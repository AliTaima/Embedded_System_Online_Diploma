/*
 * Stm32_F103x6.h
 *
 *  Created on: Feb 22, 2023
 *      Author: Ali Mohamed Taima
 */

#ifndef INC_STM32_F103X6_H_
#define INC_STM32_F103X6_H_

//-----------------------------
//Includes
//-----------------------------

#include <stdlib.h>
#include <stdint.h>
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_Memory_BASE						0x08000000UL
#define System_Memory_BASE						0x1FFFF000UL
#define SRAM_BASE								0x20000000UL

#define Peripherals_BASE						0x40000000UL
#define Cortex_M3_Internal_Peripherals_BASE		0xE0000000UL
#define NVIC_BASE								0xE000E100UL

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: NVIC Register map
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_ISER0						*(volatile uint32_t *)(NVIC_BASE + 0X0)
#define NVIC_ISER1						*(volatile uint32_t *)(NVIC_BASE + 0X4)
#define NVIC_ISER2						*(volatile uint32_t *)(NVIC_BASE + 0X8)
#define NVIC_ICER0						*(volatile uint32_t *)(NVIC_BASE + 0X80)
#define NVIC_ICER1						*(volatile uint32_t *)(NVIC_BASE + 0X84)
#define NVIC_ICER2						*(volatile uint32_t *)(NVIC_BASE + 0X88)
//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------
#define RCC_BASE 		0x40021000UL
//#define RCC_BASE 		(Peripherals_BASE+ 0x00021000UL)

//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

//GPIO
//A, B fully included in LQF48 Package
#define GPIOA_BASE 		0x40010800UL
#define GPIOB_BASE 		0x40010C00UL


//C, D partial included in LQF48 package
#define GPIOC_BASE 		0x40011000UL
#define GPIOD_BASE 		0x40011400UL
//E not included in LQF48 Package
#define GPIOE_BASE 		0x40011800UL

//------------------------------------
#define  EXTI_BASE		0x40010400UL
#define  AFIO_BASE		0x40010000UL

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------
//===============================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;


}RCC_TypeDef;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	// I will combine the 4 EXTICR in array of 4 elements
	volatile uint32_t EXTICR[4];

	uint32_t RESERVED0;//0x18
	volatile uint32_t MAPR2;//0x1C

}AFIO_TypeDef;
//===================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*-
//GPIO_TypeDef *GPIOA = (GPIO_TypeDef *)GPIOA_BASE;
//GPIO_TypeDef *GPIOA = GPIOA;
#define GPIOA		((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB		((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC		((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD		((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE		((GPIO_TypeDef *)GPIOE_BASE)

#define RCC			((RCC_TypeDef *)RCC_BASE)
#define EXTI		((EXTI_TypeDef *)EXTI_BASE)
#define AFIO		((AFIO_TypeDef *)AFIO_BASE)


//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//GPIO
#define RCC_GPIOA_CLK_EN()		(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()		(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()		(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()		(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()		(RCC->APB2ENR |= 1<<6)
//AFIO
#define AFIO_GPIOE_CLK_EN()		(RCC->APB2ENR |= 1<<0)

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*


//-*-*-*-*-*-*-*-*-*-*-*-
//IVT
//-*-*-*-*-*-*-*-*-*-*-*
// EXTI
#define EXTI0_IRQ		6
#define EXTI1_IRQ		7
#define EXTI2_IRQ		8
#define EXTI3_IRQ		9
#define EXTI4_IRQ		10
#define EXTI5_IRQ		23
#define EXTI6_IRQ		23
#define EXTI7_IRQ		23
#define EXTI8_IRQ		23
#define EXTI9_IRQ		23
#define EXTI10_IRQ		40
#define EXTI11_IRQ		40
#define EXTI12_IRQ		40
#define EXTI13_IRQ		40
#define EXTI14_IRQ		40
#define EXTI15_IRQ		40

//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC IRQ enable/Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_IRQ6_EXTI0_Enable				(NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Enable				(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Enable				(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Enable				(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Enable				(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Enable			(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Enable			(NVIC_ISER1 |= 1<<8) // As 40 is in rage 32->63 which is for ISER1 (40 - 32)

//Disabling --> we use the same but change to ICER0 & ICER1
#define NVIC_IRQ6_EXTI0_Disable				(NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Disable				(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Disable				(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Disable				(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Disable			(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Disable			(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Disable		(NVIC_ICER1 |= 1<<8) // As 40 is in rage 32->63 which is for ISER1 (40 - 32)


#endif /* INC_STM32_F103X6_H_ */