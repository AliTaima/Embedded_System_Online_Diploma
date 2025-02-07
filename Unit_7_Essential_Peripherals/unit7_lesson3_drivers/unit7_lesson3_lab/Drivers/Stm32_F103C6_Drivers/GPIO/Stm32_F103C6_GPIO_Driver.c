/*
 * Stm32_F103C6_GPIO_Driver.c
 *
 *  Created on: Feb 22, 2023
 *      Author: Ali Mohamed Taima
 */

#include "Stm32_F103C6_GPIO_Driver.h"

uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	default:
		return 0;
	}

}
/**================================================================
 * @Fn			- MCAL_GPIO_Init
 * @brief 		- Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param [in] 	-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	-PinConfig pointer to a GPIO_PinConfig_t structure that contains
 * 				 the configuration information for the specified GPIO PIN.
 * @retval		-none
 * Note			-Stem32f103C6 MCU has GPIO A, B, C, D, E Modules
 * 				 But LQFP48 Package has only GPIO A, B, PART of C/D exported as external PINS from the MCU
 */
void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_PinConfig_t* PinConfig)
{
	// Port configuration register low (GPIOx_CRL) --> Configures PINS from 0 >> 7
	// Port configuration register High (GPIOx_CRH) --> Configures PINS from 8 >> 15
	volatile uint32_t* configRegister = NULL;
	uint8_t PIN_config = 0;
	configRegister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH;
	//if pin is output
	//Clear CNF[1:0] MODE8[1:0]
	(*configRegister) &= ~(0xf<<Get_CRLH_Position(PinConfig->GPIO_PinNumber));
	if( (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP) )
	{
		//Set CNF[1:0] MODE8[1:0]
		PIN_config = ((((PinConfig->GPIO_MODE - 4)<<2) | (PinConfig->GPIO_Output_Speed)) & 0x0f);
	}
	// if pin is input
	else // MODE = 00: input mode(reset state)
	{
		if((PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO) || (PinConfig->GPIO_MODE == GPIO_MODE_Analog))
		{
			//Set CNF[1:0], MODE8[1:0] = 00
			PIN_config = ((((PinConfig->GPIO_MODE)<<2) | 0x0) & 0x0f);

		}else if(PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT) //Consider it as input floating
		{
			//Set CNF[1:0], MODE8[1:0] = 00
			PIN_config = ( (((GPIO_MODE_INPUT_FLO)<<2) | 0x0) & 0x0f);
		}
		else //PU PD Input
		{
			PIN_config = ( (((GPIO_MODE_INPUT_PU )<<2) | 0x0) & 0x0f);
			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				//Table 20. Port bit configuration table --> PxODR register = 1
				GPIOx->ODR |= PinConfig->GPIO_PinNumber; // I make the shift in the macros itself, so I don't make here

			}else
			{
				//Table 20. Port bit configuration table --> PxODR register = 1
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber); // I make the shift in the macros itself, so I don't make here
			}
		}

	}
	// Write on the CRL or CRH
	(*configRegister) |= ((PIN_config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
}
/**================================================================
 * @Fn			- MCAL_GPIO_DeInit
 * @brief 		- Reset all the GPIO Registers
 * @param [in] 	-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval		-none
 * Note			-none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
	// If you don't have a reset controller, so you need to reset manual
	//	GPIOx->BRR = 0x00000000;
	//	GPIOx->BSRR = 0x00000000;
	//	GPIOx->CRH = 0x44444444;
	//	GPIOx->CRL = 0x44444444;
	////	GPIOx->IDR = 0X00000000; --> can't write as it read only
	//	GPIOx->LCKR = 0X00000000;
	//	GPIOx->ODR = 0X00000000;
	//------------- But we have reset controller in stm32, so we can use it better ---------------------
	//APB2 peripheral reset register (RCC_APB2RSTR) ---> Set and cleared by software
	if(GPIOx == GPIOA)
	{
		//Bit 2 IOPARST: I/O port A reset
		//Set and cleared by software.
		//0: No effect
		//1: Reset I/O port A
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}else if(GPIOx == GPIOB)
	{
		//Bit 3 IOPBRST: IO port B reset
		//Set and cleared by software.
		//0: No effect
		//1: Reset I/O port B
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}else if(GPIOx == GPIOC)
	{
		//Bit 4 IOPCRST: IO port C reset
		//Set and cleared by software.
		//0: No effect
		//1: Reset I/O port C
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}else if(GPIOx == GPIOD)
	{
		//Bit 5 IOPDRST: I/O port D reset
		//Set and cleared by software.
		//0: No effect
		//1: Reset I/O port D
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}else if(GPIOx == GPIOE)
	{
		//Bit 6 IOPERST: I/O port E reset
		//Set and cleared by software.
		//0: No effect
		//1: Reset I:O port E
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}

}

/**================================================================
 * @Fn			- MCAL_GPIO_ReadPin
 * @brief 		- Read Specific PIN
 * @param [in] 	-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	-PinNumber: Set Pin Number according @ref GPIO_PIN_define
 * @retval		-The input pin value (two values based on @ref GPIO_PIN_state)
 * Note			-none
 */

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber)
{
	uint8_t BitStatus;
	if(((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_RESET)
	{
		BitStatus = GPIO_PIN_SET;
	}else
	{
		BitStatus = GPIO_PIN_RESET;
	}
	return BitStatus;
}

/**================================================================
 * @Fn			- MCAL_GPIO_ReadPort
 * @brief 		- Read the whole port
 * @param [in] 	-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	-PinNumber: Set Pin Number according @ref GPIO_PIN_define
 * @retval		-The input port value
 * Note			-none
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx)
{
	uint16_t PortValue;
	PortValue = (uint16_t)GPIOx->IDR;
	return PortValue;

}
/**================================================================
 * @Fn			- MCAL_GPIO_WritePin
 * @brief 		- Write  Specific PIN
 * @param [in] 	-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	-PinNumber: Specifies Pin Number according @ref GPIO_PIN_define
 * @param [in] 	-Value: Specifies the port bit to read according @ref GPIO_PIN_define
 * @retval		-None
 * Note			-none
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t PinNumber, uint8_t Value)
{
	if(Value != GPIO_PIN_RESET)
	{
		// GPIOx->ODR |= PinNumber;
		// ---OR--------
		/*
		 * Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Set the corresponding ODRx bit
		 */
		GPIOx->BSRR = (uint32_t)PinNumber; //(uint32_t) as I write on 32-bits register
	}else
	{
		/*
		 * Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
			These bits are write-only and can be accessed in Word mode only.
			0: No action on the corresponding ODRx bit
			1: Reset the corresponding ODRx bit
		 */
		GPIOx->BRR = (uint32_t)PinNumber;
	}
}
/**================================================================
 * @Fn			- MCAL_GPIO_WritePort
 * @brief 		- Write  the whole output port
 * @param [in] 	-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval		-None
 * Note			-none
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx, uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}
/**================================================================
 * @Fn			- MCAL_GPIO_TogglePin
 * @brief 		- Toggle specific GPIO pin
 * @param [in] 	-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	-Value: Specifies the port bit to read according @ref GPIO_PIN_define
 * @retval		-None
 * Note			-none
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= (uint32_t)(PinNumber);
}
/**================================================================
 * @Fn			- MCAL_GPIO_LockPin
 * @brief 		- The locking mechanism allows the IO configuration to be forzen
 * @param [in] 	-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	-Value: Specifies the port bit to read according @ref GPIO_PIN_define
 * @retval		-OK if pin config is locked OR ERROR if pin not locked (OK & ERROR are defined @ref GPIO_RETURN_LOCK
 * Note			-none
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber)
{
	/*
	 * Bit 16 LCKK[16]: Lock key
		This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
		0: Port configuration lock key not active
		1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
		LOCK key writing sequence:
		Write 1
		Write 0
		Write 1
		Read 0
		Read 1 (this read is optional but confirms that the lock is active)
		Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
		Any error in the lock sequence will abort the lock.
		Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
		These bits are read write but can only be written when the LCKK bit is 0.
		0: Port configuration not locked
		1: Port configuration locked.
	 */
	// Set LCKK[16]
	volatile uint32_t tmp = 1<<16;
	// Set LCKy
	tmp |= PinNumber;
//	Write 1
	GPIOx->LCKR = tmp;
//	Write 0
	GPIOx->LCKR = PinNumber;

//	Write 1
	GPIOx->LCKR = tmp;
//	Read 0
	tmp = GPIOx->LCKR;
//	Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOx->LCKR & (1<<16)))
	{
		return GPIO_RETURN_LOCK_Enabled;
	}else
	{
		return GPIO_RETURN_LOCK_ERROR;
	}
}
