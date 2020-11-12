/**
  ******************************************************************************
  * @Company    : Quadrar Tecnologia Ltda.
  * @file       : quadrar_loraone.c
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
  *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
// Standard C Library includes
#include "string.h"
#include "stdio.h"

// APP includes
#include "quadrar_loraone.h"
#include "usart.h"


/* Private define ------------------------------------------------------------*/
//#define BS              0x08
//#define LF              0x0A
//#define CR              0x0D
//#define S_OFF           (0)
//#define S_ON            (1)
//#define RXUNSOL         (10)


/* Private typedef -----------------------------------------------------------*/
static const char* LORAONE_MSG_OK[] = {            /** OK messages */
		LoRaONE_VERSION,LoRaONE_VERSION2, "OK",NULL
};

static const char* LORAONE_MSG_ERROR[] = {         /** Error messages */
  "AT_ERROR", "AT_PARAM_ERROR", "AT_BUSY_ERROR", "AT_TEST_PARAM_OVERFLOW", "AT_NO_CLASSB_ENABLE", "AT_NO_NETWORK_JOINED", "AT_RX_ERROR", NULL
};

/* Private variables ---------------------------------------------------------*/
extern quadrar_uart_rx_t lora;

/* Private function prototypes -----------------------------------------------*/
static int32_t quadrar_loraone_at_send		(char* cmd, char* presp, uint32_t max);
static int32_t quadrar_loraone_rxline		(char* pline, uint32_t max);
static int32_t quadrar_loraone_find_msg		(char* line, const char* table[]);
/**
******************************************************************************
* Local functions
******************************************************************************
*/

/**
* @brief   : Init the LoRaONE Module
* @param   : none
* @retval  : OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_init(void)
{
	int32_t res = 0;
	static quadrar_loraone_data_t loraOneId;

	// Initiate the Uart Control
	lora.dataComplete = 0;
	lora.pos = 0;
	memset(lora.bufferRx, 0x00, sizeof(lora.bufferRx));
	memset(lora.bufferData, 0x00, sizeof(lora.bufferData));

	loraOneId.NWKSKEY = LoRaONE_NWKSKEY;
	loraOneId.APPSKEY = LoRaONE_APPSKEY;
	loraOneId.DADDR   = LoRaONE_DADDR;
	loraOneId.APPEUI  = LoRaONE_APPEUI;

    // Reseting the module
    res = quadrar_loraone_reset();
    if(res) {
    	return res;
    }

    // Sends AT command to check if module is live
    res = quadrar_loraone_at_send("", NULL, 0);
    if(res) {
    	return res;
    }

    // Turn off the notification from the network messages
    res = quadrar_loraone_at_send("+CFM=0", NULL, 0);
    if(res) {
    	return res;
    }

    // Set for no retries
    res = quadrar_loraone_at_send("+RETRY=0", NULL, 0);
    if(res) {
    	return res;
    }

    // Set the APPSKEY
    res = quadrar_loraone_setAPPSKEY(loraOneId.APPSKEY,NULL);
    if(res){
    	return res;
    }

    // Set the NWKSKEY
    quadrar_loraone_setNWKSKEY(loraOneId.NWKSKEY, NULL);
    if(res){
    	return res;
    }

    // Set the DADDR
    quadrar_loraone_setDADDR(loraOneId.DADDR, NULL);
    if(res){
    	return res;
    }

    // Set the APPEUI
    quadrar_loraone_setAPPEUI(loraOneId.APPEUI, NULL);
    if(res){
    	return res;
    }

    // Establishes join mode 0 (ABP)
    res = quadrar_loraone_join(QUADRAR_LORAONE_ABP);
    if(res) {
    	return res;
    }
    return res;
}

/**
* @brief   : Resets the LoRaONE Module
* @param   : none
* @retval  : OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_reset(void)
{
	uint32_t res = 0;

	// Sends ATZ command to reset the module
	res = quadrar_loraone_at_send("Z", NULL, 0);
	return res;
}

/**
* @brief   : Puts the LoRaONE Module in low power mode
* @param   : none
* @retval  : OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_sleep(void)
{
	uint32_t res = 0;

	// Sends AT+SLEEP command to put the module in low power
	res = quadrar_loraone_at_send("+SLEEP", NULL, 0);
	return res;
}

/**
* @brief   : Joins the LoRaONE Module in the network
* @param   : QUADRAR_LORAONE_JOIN
* @retval  : OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_join(quadrar_loraone_join_t mode)
{
	uint32_t res = 0;

	// Establishes join mode 0 (ABP)
	if (mode == QUADRAR_LORAONE_ABP){
		res = quadrar_loraone_at_send("+NJM=0", NULL, 0);
	}

	// Establishes join mode 1 (OTAA)
	else if (mode == QUADRAR_LORAONE_OTAA){
		res = quadrar_loraone_at_send("+NJM=1", NULL, 0);
	}

	else{
		res = -1;
	}

	return res;
}

/**
* @brief   		: Sends data through lora radio
* @param   port	: Broker port who will receive data
* @param   data : Pointer to the data to be sent
* @retval  		: OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_send_data(int port, char* data)
{
	char buf_lora[100] = {0x00};
	int32_t res = 0;

	memset(buf_lora, 0x00, sizeof(buf_lora));

	// formating the data
	sprintf(buf_lora, "+SEND=%d:%s", port, data);

    // Establishes join mode 0 (ABP)
    res = quadrar_loraone_join(QUADRAR_LORAONE_ABP);
    if(res) {
    	return res;
    }
	// sending message
	res = quadrar_loraone_at_send(buf_lora,NULL,0);
	return res;
}

/**
* @brief   		: Get the Device EUI from the module
* @param   DEUI : Pointer to retrieve the data
* @retval  		: OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_getDEUI(char* DEUI)
{
	uint32_t res = 0;

	// Gets the Device EUI
	res = quadrar_loraone_at_send("+DEUI=?", DEUI, 0);
	return res;
}

/**
* @brief   			: Set the APPLICATION EUI
* @param   APPEUI 	: Pointer to the APPEUI information
* @param   resp 	: Pointer to retrieve the hash information loaded into the module
* @retval  			: OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_setAPPEUI(char* APPEUI, char* resp)
{
	char buf_lora[100] = {0x00};
	int32_t res = 0;

	memset(buf_lora, 0x00, sizeof(buf_lora));

	// formating the data
	sprintf(buf_lora, "+APPEUI=%s", APPEUI);

	// Sets the APPLICATION EUI
	res = quadrar_loraone_at_send(buf_lora, resp, 0);
	return res;
}

/**
* @brief   			: Set the DEVICE ADDRESS
* @param   DADDR 	: Pointer to the DADDR information
* @param   resp 	: Pointer to retrieve the hash information loaded into the module
* @retval  			: OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_setDADDR(char* DADDR, char* resp)
{
	char buf_lora[100] = {0x00};
	int32_t res = 0;

	memset(buf_lora, 0x00, sizeof(buf_lora));

	// formating the data
	sprintf(buf_lora, "+DADDR=%s", DADDR);

	// Sets the APPLICATION EUI
	res = quadrar_loraone_at_send(buf_lora, resp, 0);
	return res;
}

/**
* @brief   			: Set the NETWORK SESSION KEY
* @param   NWKSKEY 	: Pointer to the DADDR information
* @param   resp 	: Pointer to retrieve the hash information loaded into the module
* @retval  			: OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_setNWKSKEY(char* NWKSKEY, char* resp)
{
	char buf_lora[100] = {0x00};
	int32_t res = 0;

	memset(buf_lora, 0x00, sizeof(buf_lora));

	// formating the data
	sprintf(buf_lora, "+NWKSKEY=%s", NWKSKEY);

	// Sets the APPLICATION EUI
	res = quadrar_loraone_at_send(buf_lora, resp, 0);
	return res;
}

/**
* @brief   			: Set the NETWORK APPLICATION KEY
* @param   APPSKEY 	: Pointer to the DADDR information
* @param   resp 	: Pointer to retrieve the hash information loaded into the module
* @retval  			: OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_setAPPSKEY(char* APPSKEY, char* resp)
{
	char buf_lora[100] = {0x00};
	int32_t res = 0;

	memset(buf_lora, 0x00, sizeof(buf_lora));

	// formating the data
	sprintf(buf_lora, "+APPSKEY=%s", APPSKEY);

	// Sets the APPLICATION EUI
	res = quadrar_loraone_at_send(buf_lora, resp, 0);
	return res;
}

/**
* @brief   		: Sends an AT command and saves responses
* @param   cmd	: Pointer to string with command to send (without the 'AT')
* @param   presp: Pointer to store response (maybe NULL)
* @param   max 	: Maximum size of the response
* @retval  		: OK or value < 0 for ERROR
*/
int32_t quadrar_loraone_at_send(char* cmd, char* presp, uint32_t max)
{
  int32_t res = 0;
  char  buf[100] = {0x00};
  char  line[100] = {0x00};
  
  /* Checks command length */
  if (2 + strlen(cmd) + 2 >= sizeof(buf)) {
    return -1;
  }
  
  /* Initialize response buffer */
  if (presp) {
    strcpy(presp, "");
  }
  
  /* Prepare command buffer */
  strcpy(buf, "AT");
  strcat(buf, cmd);
  strcat(buf, "\r");
  
  /* Sends command */
  res = uart_send_data((uint8_t*)buf, (uint8_t)strlen(buf));
  if (res) {
    return res;
  }
  
  HAL_Delay(2000);

  //return 0;

  /* Receive response line */
  res = quadrar_loraone_rxline(line, sizeof(line));
  if (res)
	  return res;
    
  /* Checks if response is empty line */
  if (strlen(line) == 0) {
	  return -2;
  }
  /* If response is OK terminates with no error */
  if (quadrar_loraone_find_msg(line, LORAONE_MSG_OK) >= 0) {
      return 0;
  }
  /* If response is ERROR, terminates with error indication */
  if (quadrar_loraone_find_msg(line, LORAONE_MSG_ERROR) >= 0) {
      return -2;
  }
  return -1;
}

/**
* Receives line terminated with CR/LF or PROMPT from device
* pline:   Pointer to store received line
* max:     Maximum size of line buffer including string terminator
* return:  Error code: 0 if OK
*/
static int32_t quadrar_loraone_rxline(char* pline, uint32_t max) {

  if(lora.dataComplete)
  {
	  strcpy(pline,lora.bufferData);
	  lora.dataComplete = 0;
	  return 0;
  }
  else
  {
	  return -1;
  }
}

/**
* Finds start message in modem response
* line:    Pointer to modem response line
* table:   Pointer to table to search for messages
* result:  Message index if found, or -1 if not found
*/
static int32_t quadrar_loraone_find_msg(char* line, const char* table[])
{
  uint32_t pos = 0;
  while (table[pos])
  {
    if (strncmp(line, table[pos], strlen(table[pos])) == 0) {
      return pos;
    }
    pos++;
  }
  return -1;
}
