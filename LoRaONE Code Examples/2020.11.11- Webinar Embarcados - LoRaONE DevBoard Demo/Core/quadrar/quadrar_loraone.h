/**
  ******************************************************************************
  * @Company    : Quadrar Tecnologia Ltda.
  * @file       : quadrar_loraone.h
  * @author     : Airton Toyofuku
  * @date       : 23/10/2020
  * @brief      : LoRaONE API implementation DEMO file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ubi_lora_H
#define __ubi_lora_H
#ifdef __cplusplus
extern "C" {
#endif
  
/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
  
  
/* Public defines ------------------------------------------------------------*/
#define ubi_lora_get_data    TimerCallback

// LoRaONE Firmware Version
#define LoRaONE_VERSION		"LoRaONE V1.1.23"
#define LoRaONE_VERSION2	"$LoRaONE V1.1.23"

// Everynet Information -> Must be exclusive for each device
#define LoRaONE_APPEUI      (char*)"fad2abc68fcb1257"
#define LoRaONE_NWKSKEY     (char*)"871f2c0d30818f67691ab3b8d34619a8"
#define LoRaONE_APPSKEY		(char*)"196989b6fdc72a58a671104c55c54bc2"
#define LoRaONE_DADDR       (char*)"a4f46af6"

/* Public typedef ------------------------------------------------------------*/   
 
typedef struct
{
    char*	 DEUI;
    char*    APPEUI;
    char*    DADDR;
    char*    NWKSKEY;
    char*    APPSKEY;
} quadrar_loraone_data_t;


typedef enum QUADRAR_LORAONE_JOIN
{
	QUADRAR_LORAONE_ABP,
	QUADRAR_LORAONE_OTAA
}quadrar_loraone_join_t;

/* Publics function prototypes -----------------------------------------------*/
int32_t quadrar_loraone_init			(void);
int32_t quadrar_loraone_reset			(void);
int32_t quadrar_loraone_sleep			(void);
int32_t quadrar_loraone_join			(quadrar_loraone_join_t mode);
int32_t quadrar_loraone_getDEUI  		(char* DEUI);
int32_t quadrar_loraone_setAPPEUI		(char* APPEUI, char* resp);
int32_t quadrar_loraone_setDADDR		(char* DADDR, char* resp);
int32_t quadrar_loraone_setNWKSKEY		(char* NWKSKEY, char* resp);
int32_t quadrar_loraone_setAPPSKEY		(char* APPSKEY, char* resp);
int32_t quadrar_loraone_send_data		(int port, char* data);

#ifdef __cplusplus
}
#endif
#endif /*__ ubi_lora_H */

/**
* @}
*/

/**
* @}
*/

/*****************************END OF FILE**************************************/
