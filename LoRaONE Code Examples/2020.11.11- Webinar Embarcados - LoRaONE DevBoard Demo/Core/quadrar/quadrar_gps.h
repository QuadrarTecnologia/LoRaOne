/**
  ******************************************************************************
  * @Company    : Quadrar Tecnologia Ltda.
  * @file       : quadrar_gps.h
  * @author     : Airton Toyofuku
  * @date       : October 2020
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
  ******************************************************************************
*/

#ifndef __quadrar_gps_H
#define __quadrar_gps_H
#ifdef __cplusplus
 extern "C" {
#endif

/*****************************************************************************/
// Includes
#include "stm32l1xx_hal.h"

/*****************************************************************************/
// Objects

// GPS NMEA last sentences
typedef struct
{
	char gprmc[100];
} quadrar_gps_nmea_t;

// GPS Position Structure
typedef struct
{
	uint8_t     fix;            ///< FIX: 1- valid, 0- invalid
    float      	latitude;       ///< Latitude  (decimal degrees from -90.0 to +90.0)
    float      	longitude;      ///< Longitude (decimal degrees from -180.0 to +180.0)
    float      	speed;          ///< Speed (meters/s)
} quadrar_gps_data_t;

/*****************************************************************************/
// Global functions

int8_t quadrar_gps_init(void);
int8_t quadrar_gps_get_data(quadrar_gps_data_t* p);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /*__ quadrar_gps_H */
