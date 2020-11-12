/**
  ******************************************************************************
  * @Company    : Quadrar Tecnologia Ltda.
  * @file       : quadrar_gps.c
  * @author     : Airton Toyofuku
  * @date       : 22/10/2020
  * @brief      : UBLOX GPS API implementation DEMO file.
  ******************************************************************************
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Quadrar Tecnologia.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Quadrar under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  *******************************************************************************/

/*****************************************************************************/
// Includes

// Standard C Library includes
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"

// Quadrar API includes
#include "quadrar_gps.h"

// Hardware includes
#include "usart.h"

/*****************************************************************************/
//Private variables
static quadrar_gps_nmea_t   NMEA;
static quadrar_gps_data_t 	GPS;

extern quadrar_uart_rx_t gps;

/*****************************************************************************/
// Private function prototypes
int8_t quadrar_gps_get_nmea(void);
int8_t quadrar_gps_parse_gprmc(char* line_rsp);

/*****************************************************************************/

/**
* @brief   : Init the GPS control
* @param   : none
* @retval  : OK or value < 0 for ERROR
*/
int8_t quadrar_gps_init(void)
{
	gps.dataComplete = 0;
	gps.pos = 0;
	memset(gps.bufferRx, 0x00, sizeof(gps.bufferRx));
	memset(gps.bufferData, 0x00, sizeof(gps.bufferData));

	return 0;
}

/**
* @brief   : Gets the GPS Data
* @param   : none
* @retval  : OK or value < 0 for ERROR
*/
int8_t quadrar_gps_get_data(quadrar_gps_data_t* p)
{
	int8_t ret = 0;

	ret = quadrar_gps_get_nmea();
	if(!ret)
	{
		memcpy(p,&GPS,sizeof(GPS));
	}
	return ret;
}

/**
* @brief   : Gets the NMEA Data from Buffer
* @param   : none
* @retval  : OK or value < 0 for ERROR
*/
int8_t quadrar_gps_get_nmea(void)
{
	int8_t ret = 0;

	if(gps.dataComplete)
	{
		// Check if the sentence is the GPRMC
		if(strncmp(gps.bufferData, "$GPRMC", strlen ("$GPRMC")) == 0)
		{
			strcpy((char*)NMEA.gprmc,(char*)gps.bufferData);
		    ret = quadrar_gps_parse_gprmc((char*)&NMEA.gprmc);
		}
		gps.dataComplete = 0;
	}
	else
	{
		ret = -1;
	}
	return ret;
}

/**
* @brief  : Parsing $GPRMC sentence.
* @param  : line_rsp: Pointer to data.
* @retval : OK or value < 0 for ERROR
*/
int8_t quadrar_gps_parse_gprmc(char* line_rsp)
{
	char bkLine[100];
    char* token;
    int32_t pos = 0;
    float degrees, minutes;

    strcpy(bkLine,line_rsp);

    // Gets NMEA $GPRMC sentence
    if (strncmp(bkLine, "$GPRMC", strlen("$GPRMC")) == 0)
    {
    	token = strtok(bkLine, ",");
        while (token != NULL)
        {
        	switch (pos)
        	{
        	case 2:
        		GPS.fix = *token;
        		break;
        	case 3:
        		GPS.latitude = strtof(token, NULL);
        		break;
        	case 4:
                if (*token == 'S')
                {
                    GPS.latitude  *= -1.0;
                }
        		break;
        	case 5:
        		GPS.longitude = strtof(token, NULL);
        		break;
        	case 6:
                if (*token == 'W')
                {
                    GPS.longitude  *= -1.0;
                }
        		break;
        	case 7:
        		GPS.speed = strtof(token, NULL);
        		GPS.speed = GPS.speed * 0.51; //(knots to m/s)
        		break;
        	default:
        		break;
        	}

            token = strtok(NULL, ",");
            ++pos;
        }

        /* Gets decimal values */
        degrees = trunc(GPS.latitude / 100.0f);
        minutes = GPS.latitude - (degrees * 100.0f);
        GPS.latitude = degrees + minutes / 60.0f;

        degrees = trunc(GPS.longitude / 100.0f);
        minutes = GPS.longitude - (degrees * 100.0f);
        GPS.longitude = degrees + minutes / 60.0f;
    }
    else
    {
    	return -1;
    }

    return 0;
}
