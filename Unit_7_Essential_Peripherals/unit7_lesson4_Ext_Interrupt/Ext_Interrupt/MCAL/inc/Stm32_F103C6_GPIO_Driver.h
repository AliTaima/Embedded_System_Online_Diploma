/*
 * Stm32_F103C6_GPIO_Driver.h
 *
 *  Created on: Feb 22, 2023
 *      Author: Ali Mohamed Taima
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_
// Includes
#include "Stm32_F103x6.h"


//--------------------------
//Configuration Structure
typedef struct
{
	// we use uint16_t as each GPIO has 16 bits
	uint16_t GPIO_PinNumber;		// Specifies the GPIO pins to be configured
								// This parameter must be a value of @ref GPIO_PIN_define

	uint8_t GPIO_MODE		; 	// specifies the operating mode for the selected pins
								// This parameter must be a value of @ref GPIO_MODE_define

	uint8_t GPIO_Output_Speed; 	// Specifies the speed for the selected pins
								//This parameter must be a value of @ref GPIO_SPEED_define

}GPIO_PinConfig_t;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Macros Configuration References
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//@ref GPIO_PIN_define

#define GPIO_PIN_0			((uint16_t)0x0001)	// Pin0 selected
#define GPIO_PIN_1			((uint16_t)0x0002)	// Pin1 selected
#define GPIO_PIN_2			((uint16_t)0x0004)	// Pin2 selected
#define GPIO_PIN_3			((uint16_t)0x0008)	// Pin3 selected
#define GPIO_PIN_4			((uint16_t)0x0010)	// Pin4 selected
#define GPIO_PIN_5			((uint16_t)0x0020)	// Pin5 selected
#define GPIO_PIN_6			((uint16_t)0x0040)	// Pin6 selected
#define GPIO_PIN_7			((uint16_t)0x0090)	// Pin7 selected
#define GPIO_PIN_8			((uint16_t)0x0100)	// Pin8 selected
#define GPIO_PIN_9			((uint16_t)0x0200)	// Pin9 selected
#define GPIO_PIN_10			((uint16_t)0x0400)	// Pin10 selected
#define GPIO_PIN_11			((uint16_t)0x0800)	// Pin11 selected
#define GPIO_PIN_12			((uint16_t)0x1000)	// Pin12 selected
#define GPIO_PIN_13			((uint16_t)0x2000)	// Pin13 selected
#define GPIO_PIN_14			((uint16_t)0x4000)	// Pin14 selected
#define GPIO_PIN_15			((uint16_t)0x8000)	// Pin15 selected
#define GPIO_PIN_All		((uint16_t)0xFFFF)	// All Pins selected

//@ref GPIO_MODE_define
//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up / pull-down
//3: Reserved
//4: General purpose output push-pull
//5: General purpose output Open-drain
//7: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function input
#define GPIO_MODE_Analog				0x00000000u	//Analog mode
#define GPIO_MODE_INPUT_FLO				0x00000001u	//floating input
#define GPIO_MODE_INPUT_PU				0x00000002u	//Input with pull-up
#define GPIO_MODE_INPUT_PD				0x00000003u	//Input with pull-down
#define GPIO_MODE_OUTPUT_PP				0x00000004u	//General Purpose output push_pull
#define GPIO_MODE_OUTPUT_OD				0x00000005u	//General Purpose output open-drain
#define GPIO_MODE_OUTPUT_AF_PP			0x00000006u	//Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD			0x00000007u	//Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT				0x00000008u	//Alternate function Input

//@ref GPIO_SPEED_define
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.
#define GPIO_SPEED_10M			0x00000001u	//Output mode, max speed 10 MHz
#define GPIO_SPEED_2M			0x00000002u	//Output mode, max speed 2 MHz.
#define GPIO_SPEED_50M			0x00000003u	//Output mode, max speed 50 MHz.

//@ref GPIO_PIN_state
#define GPIO_PIN_SET	1
#define GPIO_PIN_RESET	0

//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_Enabled	1
#define GPIO_RETURN_LOCK_ERROR		0
/*
 * ===========================================================================
 * 			 		APIs Supported by "MCAL GPIO DRIVERR"
 * ===========================================================================
 */
void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t PinNumber, uint8_t Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx, uint16_t Value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);





#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
