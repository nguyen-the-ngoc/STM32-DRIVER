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

//Phân chia vùng nhớ
#define FLASH_BASEADDR		0x08000000UL		//Main memory
#define SRAM_BASEADDR		0x20000000UL		//The SRAM start address

//Phân chia vùng nhớ cho Peripheral
#define PERIPH_BASEADDR		0x40000000UL		//Flash memory interface registers

//Phân chia các Bus
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		(APB1PERIPH_BASEADDR + 0x00010000UL)
#define AHBPERIPH_BASEADDR		(APB1PERIPH_BASEADDR + 0x00018000UL)

//Cấu hình địa chỉ cho từng PORT						|| APB2
#define GPIOA_BASEADDR		(APB2PERIPH_BASEADDR + 0x0800UL)
#define GPIOB_BASEADDR		(APB2PERIPH_BASEADDR + 0x0C00UL)
#define GPIOC_BASEADDR		(APB2PERIPH_BASEADDR + 0x1000UL)
#define GPIOD_BASEADDR		(APB2PERIPH_BASEADDR + 0x1400UL)
#define GPIOE_BASEADDR		(APB2PERIPH_BASEADDR + 0x1800UL)
#define GPIOF_BASEADDR		(APB2PERIPH_BASEADDR + 0x1C00UL)
#define GPIOG_BASEADDR		(APB2PERIPH_BASEADDR + 0x2000UL)
#define EXTI_BASEADDR		(APB2PERIPH_BASEADDR + 0x0400UL)

//Cấu hình địa chỉ RCC - cấp Clock cho BUS APB2		|| AHB
#define RCC_BASEADDR			(AHBPERIPH_BASEADDR + 0x1000UL)

//Khai báo các thanh ghi của GPIO
typedef struct{
	__vo uint32_t CRL;
	__vo uint32_t CRH;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t BRR;
	__vo uint32_t LCKR;
}GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASEADDR)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASEADDR)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASEADDR)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASEADDR)
#define GPIOE ((GPIO_TypeDef *)GPIOE_BASEADDR)
#define GPIOF ((GPIO_TypeDef *)GPIOF_BASEADDR)
#define GPIOG ((GPIO_TypeDef *)GPIOG_BASEADDR)

//Khai báo các thanh ghi của RCC
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
}RCC_TypeDef;

#define RCC ((RCC_TypeDef *)RCC_BASEADDR)

//Khai bao các thanh ghi của EXTI
typedef struct{
	__vo uint32_t IMR;						/* Offset: 0x00 */
	__vo uint32_t EMR;						/* Offset: 0x04 */
	__vo uint32_t RTSR;						/* Offset: 0x08 */
	__vo uint32_t FTSR;						/* Offset: 0x0C */
	__vo uint32_t SWIER;					/* Offset: 0x10 */
	__vo uint32_t PR;						/* Offset: 0x14 */
}EXTI_TypeDef;

#define EXTI ((EXTI_TypeDef *)EXTI_BASEADDR)

//Clock Enable Macro for GPTIx Peripheral
#define GPIOA_PCLK_EN() (RCC->APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN() (RCC->APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN() (RCC->APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN() (RCC->APB2ENR |= (1 << 5))
#define GPIOE_PCLK_EN() (RCC->APB2ENR |= (1 << 6))
#define GPIOF_PCLK_EN() (RCC->APB2ENR |= (1 << 7))
#define GPIOG_PCLK_EN() (RCC->APB2ENR |= (1 << 8))

//Clock Disable Macro for GPTIx Peripheral
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

#endif /* STM32_103_H_ */
