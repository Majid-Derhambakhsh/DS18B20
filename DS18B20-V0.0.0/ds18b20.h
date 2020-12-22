/*
------------------------------------------------------------------------------
~ File   : ds18b20.h
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

#ifndef __DS18B20_H_
#define __DS18B20_H_

/*----------------------------------------------------------*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <stdint.h>

#include "ds18b20_conf.h"

/* ------------------------------------------------------------------ */

#ifdef __CODEVISIONAVR__  /* Check compiler */

#pragma warn_unref_func- /* Disable 'unused function' warning */

#include "GPIO_UNIT/gpio_unit.h" /* Import gpio lib */

#include <delay.h>       /* Import delay library */

/* ------------------------------------------------------------------ */

#elif defined(__GNUC__) && !defined(USE_HAL_DRIVER)  /* Check compiler */

#pragma GCC diagnostic ignored "-Wunused-function" /* Disable 'unused function' warning */

#include "GPIO_UNIT/gpio_unit.h" /* Import gpio lib */

#include <util/delay.h>  /* Import delay library */

/* ------------------------------------------------------------------ */

#elif defined(USE_HAL_DRIVER)  /* Check driver */

	/* --------------- Check Mainstream series --------------- */
	
	#ifdef STM32F0
		#include "stm32f0xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F1)
		#include "stm32f1xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F2)
		#include "stm32f2xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F3)
		#include "stm32f3xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F4)
		#include "stm32f4xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F7)
		#include "stm32f7xx_hal.h"       /* Import HAL library */
	#elif defined(STM32G0)
		#include "stm32g0xx_hal.h"       /* Import HAL library */
	#elif defined(STM32G4)
		#include "stm32g4xx_hal.h"       /* Import HAL library */

	/* ------------ Check High Performance series ------------ */

	#elif defined(STM32H7)
		#include "stm32h7xx_hal.h"       /* Import HAL library */

	/* ------------ Check Ultra low power series ------------- */

	#elif defined(STM32L0)
		#include "stm32l0xx_hal.h"       /* Import HAL library */
	#elif defined(STM32L1)
		#include "stm32l1xx_hal.h"       /* Import HAL library */
	#elif defined(STM32L5)
		#include "stm32l5xx_hal.h"       /* Import HAL library */
	#elif defined(STM32L4)
		#include "stm32l4xx_hal.h"       /* Import HAL library */
	#elif defined(STM32H7)
		#include "stm32h7xx_hal.h"       /* Import HAL library */
	#else
	#endif /* STM32F1 */

	/* ------------------------------------------------------- */

	#if defined ( __ICCARM__ ) /* ICCARM Compiler */

	#pragma diag_suppress=Pe177   /* Disable 'unused function' warning */

	#elif defined   (  __GNUC__  ) /* GNU Compiler */

	#pragma diag_suppress 177     /* Disable 'unused function' warning */

	#endif /* __ICCARM__ */

/* ------------------------------------------------------------------ */

#else                     /* Compiler not found */

#error Chip or Library not supported  /* Send error */

#endif /* __CODEVISIONAVR__ */

/* ------------------------------------------------------------------ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifndef Delay_US

#error [DS-01] You are not define the usecond delay function

#endif

/* ------------------------ Library ------------------------ */
#define _DS18B20_LIBRARY_VERSION 0.0.0

/* ------------------------ Timing ------------------------- */
/* :::::::::: u second :::::::::: */
#define _DS18B20_1US_WAIT    1U
#define _DS18B20_2US_WAIT    2U
#define _DS18B20_60US_WAIT   60U
#define _DS18B20_80US_WAIT   80U
#define _DS18B20_400US_WAIT  400U
#define _DS18B20_480US_WAIT  480U

/* :::::::::: m second :::::::::: */
#ifndef _DS18B20_REINIT_DELAY

#define _DS18B20_REINIT_DELAY  800U

#endif

/* ------------------------ Public ------------------------- */
#define _DS18B20_T_DIVIDER   16.0f
#define _DS18B20_BYTE_LENGTH 8

/* ---------------------- By compiler ---------------------- */
#ifdef USE_HAL_DRIVER
	
	#define GPIO_SetOutputPin(GPIOx, Pinx)       HAL_GPIO_WritePin((GPIOx), (Pinx), GPIO_PIN_SET)
	#define GPIO_ResetOutputPin(GPIOx, Pinx)     HAL_GPIO_WritePin((GPIOx), (Pinx), GPIO_PIN_RESET)
	
	#define GPIO_ReadInputPin(GPIOx, Pinx)       HAL_GPIO_ReadPin((GPIOx), (Pinx))
	
	#define GPIO_SetPinAsInput()                 HAL_GPIO_SetPinAsInput()
	#define GPIO_SetPinAsOutput()                HAL_GPIO_SetPinAsOutput()
	
	#ifndef Delay_MS
	
	#define Delay_MS(tim)                        HAL_Delay((tim))
	
	#endif /* Delay_MS */
	
	/* ........................... */
	#define _GPIO_PIN_LOW   GPIO_PIN_RESET
	#define _GPIO_PIN_HIGH  GPIO_PIN_SET
	
#elif defined(USE_LL_DRIVER)
	
	#define GPIO_SetOutputPin(GPIOx, Pinx)       LL_GPIO_SetOutputPin((GPIOx), (Pinx))
	#define GPIO_ResetOutputPin(GPIOx, Pinx)     LL_GPIO_ResetOutputPin((GPIOx), (Pinx))
	
	#define GPIO_ReadInputPin(GPIOx, Pinx)       LL_GPIO_SetOutputPin((GPIOx), (Pinx))
	
	/* ........................... */
	#define _GPIO_PIN_LOW   0
	#define _GPIO_PIN_HIGH  1
	
#endif /* USE_HAL_DRIVER */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
enum DS18B20CMD_TypeDef
{
	
	_DS18B20_CMD_READ_ROM          = 0x33,
	_DS18B20_CMD_CONVERT_T         = 0x44,
	_DS18B20_CMD_MATCH_ROM         = 0x55,
	_DS18B20_CMD_READ_SCRATCHPAD   = 0xBE,
	_DS18B20_CMD_WRITE_SCRATCHPAD  = 0x4E,
	_DS18B20_CMD_COPY_SCRATCHPAD   = 0x48,
	_DS18B20_CMD_RECALL_E2         = 0xB8,
	_DS18B20_CMD_READ_POWER_SUPPLY = 0xB4,
	_DS18B20_CMD_SKIP_ROM          = 0xCC,
	_DS18B20_CMD_ALARM_SEARCH_ROM  = 0xEC,
	_DS18B20_CMD_SEARCH_ROM        = 0xF0,
	
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Class ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ::::::::::::::: Pin Configuration ::::::::::::::: */
#ifdef USE_HAL_DRIVER

void HAL_GPIO_SetPinAsInput(void);
void HAL_GPIO_SetPinAsOutput(void);

#endif /* USE_HAL_DRIVER */

/* :::::::::::::::::: Initialize ::::::::::::::::::: */
uint8_t DS18B20_Init(void);

uint8_t DS18B20_Start(void);

/* :::::::::::::: Rom Data Management :::::::::::::: */
void    DS18B20_WriteData(uint8_t Data);
uint8_t DS18B20_ReadData(void);

/* :::::::::::::::: Get Temperature :::::::::::::::: */
float DS18B20_GetTemperature(void);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#endif /* __DS18B20_H_ */
