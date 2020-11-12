

/* ------------------------DS18B20--------------------------- */

#define	_DS18B20_USE_FREERTOS           0
#define _DS18B20_MAX_SENSORS            1
#define DS18B20_GPIO_Port               GPIOA
#define DS18B20_Pin                     GPIO_PIN_0
#define	_DS18B20_GPIO					DS18B20_GPIO_Port
#define	_DS18B20_PIN					DS18B20_Pin
#define	_DS18B20_CONVERT_TIMEOUT_MS		8000

#if (_DS18B20_USE_FREERTOS==1)
#define	_DS18B20_UPDATE_INTERVAL_MS		10000	//  (((	if==0  >> Ds18b20_ManualConvert()  )))    ((( if>0  >>>> Auto refresh )))
#endif

/* ---------------------------------------------------------- */

#ifdef __cplusplus
}
#endif /*__ ds18b20_config_H */
