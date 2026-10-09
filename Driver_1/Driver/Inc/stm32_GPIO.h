/*
 * stm32_GPIO.h
 *
 *  Created on: Sep 7, 2026
 *      Author: theng
 */

#ifndef INC_STM32_GPIO_H_
#define INC_STM32_GPIO_H_
#include "stm32_103.h"

#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15

/* GPIO Mode */
#define GPIO_MODE_INPUT		0 // Input mode (reset state)
#define GPIO_MODE_ANALOG	1 // Analog mode
#define GPIO_MODE_OUTPUT	2 // Output mode
#define GPIO_MODE_IT_FT		3 // Interrupt mode, falling edge trigger
#define GPIO_MODE_IT_RT		4 // Interrupt mode, rising edge trigger
#define GPIO_MODE_IT_RFT	5 // Interrupt mode, rising/falling edge trigger

/* CNF field values; meaning depends on input/output mode */
#define GPIO_CNF_ANALOG             0
#define GPIO_CNF_INPUT_FLOATING     1
#define GPIO_CNF_INPUT_PU_PD        2
#define GPIO_CNF_OUTPUT_PP          0
#define GPIO_CNF_OUTPUT_OD          1
#define GPIO_CNF_AF_PP              2
#define GPIO_CNF_AF_OD              3

/* GPIO Speed */
#define GPIO_INPUT_MODE_STATE		0 // Input mode (reset state)
#define GPIO_SPEED_MEDIUM	        1 // Output mode, max speed 10 MHz
#define GPIO_SPEED_LOW		        2 // Output mode, max speed 2 MHz
#define GPIO_SPEED_HIGH	            3 // Output mode, max speed 50 MHz

typedef struct
{
    __vo uint8_t GPIO_Pin_Number;
    __vo uint8_t GPIO_Pin_Mode;
    __vo uint8_t GPIO_Type;
    __vo uint8_t GPIO_Pin_Speed;
}GPIO_Config_t;

typedef struct
{
    GPIO_Typedef_t *pGPIOx;
    GPIO_Config_t *pGPIO_Config;
}GPIO_Handle_t;

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_Typedef_t *pGPIOx);
void GPIO_PeriClockControl(GPIO_Typedef_t *pGPIOx, uint8_t EnorDi);
void GPIO_WriteToOutputPin(GPIO_Typedef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_ToggleOutputPin(GPIO_Typedef_t *pGPIOx, uint8_t PinNumber);
uint8_t GPIO_ReadFromInputPin(GPIO_Typedef_t *pGPIOx, uint8_t PinNumber);
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);
#endif /* INC_STM32_GPIO_H_ */
