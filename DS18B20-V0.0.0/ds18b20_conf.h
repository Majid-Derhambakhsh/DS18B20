/*
------------------------------------------------------------------------------
~ File   : ds18b20_conf.h
~ Author : Majid Derhambakhsh
~ Version: V0.0.0
~ Created: 12/16/2020 08:31:00 PM
~ Brief  :
~ Support:
		   E-Mail : Majid.do16@gmail.com (subject : Embedded Library Support)

		   Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:

~ Attention  :

~ Changes    :
------------------------------------------------------------------------------
*/

#ifndef __DS18B20_CONF_H_
#define __DS18B20_CONF_H_

/* --- Required Driver.Library---- */
/* For AVR */
//#include "x.h"

/* For STM32 */
//#include "x.h"

/* -------- Configuration -------- */
/* GPIO */
#define _DS18B20_GPIO          GPIOx
#define _DS18B20_PIN           GPIO_PIN_x

#define _DS18B20_REINIT_DELAY  1000U

/* Delay Functions */
#define Delay_MS(tim)          HAL_Delay((tim))
#define Delay_US(tim)          HAL_Delay((tim))

/* Microcontroller Series */
#define STM32F1

/*
	Guide   :
			  
			  _DS18B20_GPIO          : DS18 Connected GPIO
			  _DS18B20_PIN           : DS18 Connected Pin of GPIO
			  
			  _DS18B20_REINIT_DELAY  : Re-Initialize delay

			  Delay_MS(tim)          : millisecond delay function
			  Delay_US(tim)          : microsecond delay function
			  
			  STM32Fx                : STM32 Microcontroller series
			  
	Example :
			  #define _DS18B20_GPIO    GPIOA
			  #define _DS18B20_PIN     GPIO_PIN_1
			  
			  #define _DS18B20_REINIT_DELAY  1000U

			  #define Delay_MS(tim)        HAL_Delay((tim))
			  #define Delay_US(tim)        HAL_Delay((tim))
			  
			  #define STM32H7

*/

#endif /* __DS18B20_CONF_H_ */
