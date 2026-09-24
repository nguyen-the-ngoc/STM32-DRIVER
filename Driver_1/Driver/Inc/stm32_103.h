/*
 * stm32_103.h
 *
 *  Created on: Sep 4, 2026
 *      Author: theng
 */

#ifndef STM32_103_H_
#define STM32_103_H_
#include "stdint.h"
#define __vo		volatile

#define NO_PR_BITS_IMPLEMENTED	4				// Number of priority bits implemented in the NVIC for STM32F103
//Memory map
#define FLASH_BASEADDR		0x08000000UL		//Main memory
#define SRAM_BASEADDR		0x20000000UL		//The SRAM start address

//Peripheral memory region
#define PERIPH_BASEADDR		0x40000000UL		//Flash memory interface registers

//Bus mapping
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		(APB1PERIPH_BASEADDR + 0x00010000UL)
#define AHBPERIPH_BASEADDR		(APB2PERIPH_BASEADDR + 0x00008000UL)

//GPIO port addresses										|| APB2
#define GPIOA_BASEADDR		(APB2PERIPH_BASEADDR + 0x0800UL)
#define GPIOB_BASEADDR		(APB2PERIPH_BASEADDR + 0x0C00UL)
#define GPIOC_BASEADDR		(APB2PERIPH_BASEADDR + 0x1000UL)
#define GPIOD_BASEADDR		(APB2PERIPH_BASEADDR + 0x1400UL)
#define GPIOE_BASEADDR		(APB2PERIPH_BASEADDR + 0x1800UL)
#define GPIOF_BASEADDR		(APB2PERIPH_BASEADDR + 0x1C00UL)
#define GPIOG_BASEADDR		(APB2PERIPH_BASEADDR + 0x2000UL)
#define EXTI_BASEADDR		(APB2PERIPH_BASEADDR + 0x0400UL)
#define AFIO_BASEADDR		(APB2PERIPH_BASEADDR + 0x0000UL)

//RCC address - clock control for the APB2 bus		|| AHB
#define RCC_BASEADDR			(PERIPH_BASEADDR + 0x21000UL)

// Define the NVIC ISERx register addresses
#define NVIC_ISER0		((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1		((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2		((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3		((__vo uint32_t*)0xE000E10C)
#define NVIC_ISER4		((__vo uint32_t*)0xE000E110)
#define NVIC_ISER5		((__vo uint32_t*)0xE000E114)
#define NVIC_ISER6		((__vo uint32_t*)0xE000E118)
#define NVIC_ISER7		((__vo uint32_t*)0xE000E11C)
// Define the NVIC ICERx register addresses
#define NVIC_ICER0		((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1		((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2		((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3		((__vo uint32_t*)0xE000E18C)
#define NVIC_ICER4		((__vo uint32_t*)0xE000E190)
#define NVIC_ICER5		((__vo uint32_t*)0xE000E194)
#define NVIC_ICER6		((__vo uint32_t*)0xE000E198)
#define NVIC_ICER7		((__vo uint32_t*)0xE000E19C)
// Define the NVIC priority register addresses
#define NVIC_IPR0		((__vo uint32_t*)0xE000E400)
#define NVIC_IPR1		((__vo uint32_t*)0xE000E404)
#define NVIC_IPR2		((__vo uint32_t*)0xE000E408)
#define NVIC_IPR3		((__vo uint32_t*)0xE000E40C)
#define NVIC_IPR4		((__vo uint32_t*)0xE000E410)
#define NVIC_IPR5		((__vo uint32_t*)0xE000E414)
#define NVIC_IPR6		((__vo uint32_t*)0xE000E418)
#define NVIC_IPR7		((__vo uint32_t*)0xE000E41C)

//GPIO register definition
typedef struct{
	__vo uint32_t CRL;
	__vo uint32_t CRH;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t BRR;
	__vo uint32_t LCKR;
}GPIO_Typedef_t;

#define GPIOA ((GPIO_Typedef_t *)GPIOA_BASEADDR)
#define GPIOB ((GPIO_Typedef_t *)GPIOB_BASEADDR)
#define GPIOC ((GPIO_Typedef_t *)GPIOC_BASEADDR)
#define GPIOD ((GPIO_Typedef_t *)GPIOD_BASEADDR)
#define GPIOE ((GPIO_Typedef_t *)GPIOE_BASEADDR)
#define GPIOF ((GPIO_Typedef_t *)GPIOF_BASEADDR)
#define GPIOG ((GPIO_Typedef_t *)GPIOG_BASEADDR)

//RCC register definition
typedef struct{
	__vo uint32_t CR;						/* Offset: 0x00 */
	__vo uint32_t CFGR;						/* Offset: 0x04 */
	__vo uint32_t CIR;						/* Offset: 0x08 */
	__vo uint32_t APB2RSTR;					/* Offset: 0x0C */
	__vo uint32_t APB1RSTR;					/* Offset: 0x10 */
	__vo uint32_t AHBENR;					/* Offset: 0x14 */
	__vo uint32_t APB2ENR;					/* Offset: 0x18 */
	__vo uint32_t APB1ENR;					/* Offset: 0x1C */
	__vo uint32_t BDCR;						/* Offset: 0x20 */
	__vo uint32_t CSR;						/* Offset: 0x24 */
}RCC_TypeDef_t;

#define RCC ((RCC_TypeDef_t *)RCC_BASEADDR)

// Define type for EXTI IRQ handler function pointer
typedef struct{
	__vo uint32_t IMR;						/* Offset: 0x00 */
	__vo uint32_t EMR;						/* Offset: 0x04 */
	__vo uint32_t RTSR;						/* Offset: 0x08 */
	__vo uint32_t FTSR;						/* Offset: 0x0C */
	__vo uint32_t SWIER;					/* Offset: 0x10 */
	__vo uint32_t PR;						/* Offset: 0x14 */
}EXTI_TypeDef_t;

#define EXTI ((EXTI_TypeDef_t *)EXTI_BASEADDR)

//AFIO register definition
typedef struct 
{
	__vo uint32_t EVCR;						/* Offset: 0x000 */
	__vo uint32_t MAPR;						/* Offset: 0x004 */
	__vo uint32_t EXTICR[4];				/* Offset: 0x008 - 0x014 */
	__vo uint32_t MAPR2;					/* Offset: 0x018 */
}AFIO_TypeDef_t;

#define AFIO ((AFIO_TypeDef_t *)AFIO_BASEADDR)

// Define the number External Interrupts (EXTI) for STM32F103
#define EXTI0_IRQn		6
#define EXTI1_IRQn		7
#define EXTI2_IRQn		8
#define EXTI3_IRQn		9
#define EXTI4_IRQn		10

// Define clock enable marcos for SYSCFG peripheral
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (1 << 0))

//Clock enable macros for GPIO peripherals
#define GPIOA_PCLK_EN() (RCC->APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN() (RCC->APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN() (RCC->APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN() (RCC->APB2ENR |= (1 << 5))
#define GPIOE_PCLK_EN() (RCC->APB2ENR |= (1 << 6))
#define GPIOF_PCLK_EN() (RCC->APB2ENR |= (1 << 7))
#define GPIOG_PCLK_EN() (RCC->APB2ENR |= (1 << 8))

//Clock disable macros for GPIO peripherals
#define GPIOA_PCLK_DIS() (RCC->APB2ENR &= ~(1 << 2))
#define GPIOB_PCLK_DIS() (RCC->APB2ENR &= ~(1 << 3))
#define GPIOC_PCLK_DIS() (RCC->APB2ENR &= ~(1 << 4))
#define GPIOD_PCLK_DIS() (RCC->APB2ENR &= ~(1 << 5))
#define GPIOE_PCLK_DIS() (RCC->APB2ENR &= ~(1 << 6))
#define GPIOF_PCLK_DIS() (RCC->APB2ENR &= ~(1 << 7))
#define GPIOG_PCLK_DIS() (RCC->APB2ENR &= ~(1 << 8))

#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define GPIO_PIN_SET SET
#define GPIO_PIN_RESET RESET	

//Reset macros for GPIO peripherals
#define	GPIOA_RS_RCC()	do	{(RCC->APB2RSTR |= (1 << 2)); (RCC->APB2RSTR &= ~(1 << 2)); } while (0)
#define	GPIOB_RS_RCC()	do	{(RCC->APB2RSTR |= (1 << 3)); (RCC->APB2RSTR &= ~(1 << 3)); } while (0)
#define	GPIOC_RS_RCC()	do	{(RCC->APB2RSTR |= (1 << 4)); (RCC->APB2RSTR &= ~(1 << 4)); } while (0)
#define	GPIOD_RS_RCC()	do	{(RCC->APB2RSTR |= (1 << 5)); (RCC->APB2RSTR &= ~(1 << 5)); } while (0)
#define	GPIOE_RS_RCC()	do	{(RCC->APB2RSTR |= (1 << 6)); (RCC->APB2RSTR &= ~(1 << 6)); } while (0)
#define	GPIOF_RS_RCC()	do	{(RCC->APB2RSTR |= (1 << 7)); (RCC->APB2RSTR &= ~(1 << 7)); } while (0)
#define	GPIOG_RS_RCC()	do	{(RCC->APB2RSTR |= (1 << 8)); (RCC->APB2RSTR &= ~(1 << 8)); } while (0)

// EXTI IRQ Number
#define GPIO_BASEADR_TO_NUMPIN(x)	((x == GPIOA) ? 0 : (x == GPIOB) ? 1 : (x == GPIOC) ? 2 : (x == GPIOD) ? 3 : (x == GPIOE) ? 4 : (x == GPIOF) ? 5 : (x == GPIOG) ? 6 : -1)
#endif /* STM32_103_H_ */
