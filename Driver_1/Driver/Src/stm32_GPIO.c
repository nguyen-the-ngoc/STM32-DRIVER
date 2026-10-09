/*
 * stm32_GPIO.c
 *
 *  Created on: Sep 7, 2026
 *      Author: theng
 */

#include "stm32_GPIO.h"

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    uint32_t temp = 0U;
    uint32_t pin_number = pGPIOHandle->pGPIO_Config->GPIO_Pin_Number;
    uint32_t mode_value = GPIO_INPUT_MODE_STATE;
    uint32_t cnf_value = pGPIOHandle->pGPIO_Config->GPIO_Type;

    if (pin_number > GPIO_PIN_NO_15)
    {
        return;
    }

    /* Determine MODE and CNF values */
    if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_INPUT)
    {
        mode_value = GPIO_INPUT_MODE_STATE;
    }
    else if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_ANALOG)
    {
        mode_value = GPIO_INPUT_MODE_STATE;
        cnf_value = GPIO_CNF_ANALOG;
    }
    else if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_OUTPUT)
    {
        mode_value = pGPIOHandle->pGPIO_Config->GPIO_Pin_Speed;
    }
    else if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_FT ||
             pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_RT ||
             pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_RFT)
    {
        mode_value = GPIO_INPUT_MODE_STATE;
    }
    else
    {
        return;
    }

    /* Configure GPIO, including pins used for interrupts */
    if (pin_number <= GPIO_PIN_NO_7)
    {
        /* Clear and set MODE: 2 bits */
        temp = pGPIOHandle->pGPIOx->CRL & ~(0x3U << (4U * pin_number));
        temp |= (mode_value & 0x3U) << (4U * pin_number);

        /* Clear and set CNF: 2 bits */
        temp &= ~(0x3U << ((4U * pin_number) + 2U));
        temp |= (cnf_value & 0x3U) << ((4U * pin_number) + 2U);

        pGPIOHandle->pGPIOx->CRL = temp;
    }
    else
    {
        /* CRH starts with pin 8 at bit 0 */
        temp = pGPIOHandle->pGPIOx->CRH & ~(0x3U << (4U * (pin_number - 8U)));
        temp |= (mode_value & 0x3U) << (4U * (pin_number - 8U));

        temp &= ~(0x3U << ((4U * (pin_number - 8U)) + 2U));
        temp |= (cnf_value & 0x3U) << ((4U * (pin_number - 8U)) + 2U);

        pGPIOHandle->pGPIOx->CRH = temp;
    }

    /* Additional configuration for interrupt modes */
    if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_FT ||
        pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_RT ||
        pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_RFT)
    {
        SYSCFG_PCLK_EN(); /* Must enable AFIO on STM32F103 */

        if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_FT)
        {
            EXTI->FTSR |= (1U << pin_number);
            EXTI->RTSR &= ~(1U << pin_number);
        }
        else if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_RT)
        {
            EXTI->FTSR &= ~(1U << pin_number);
            EXTI->RTSR |= (1U << pin_number);
        }
        else
        {
            EXTI->FTSR |= (1U << pin_number);
            EXTI->RTSR |= (1U << pin_number);
        }

        uint32_t portcode = GPIO_BASEADR_TO_NUMPIN(pGPIOHandle->pGPIOx);
        uint32_t temp1 = pin_number % 4U;
        uint32_t temp2 = pin_number / 4U;

        /* Change only the selected EXTI field */
        temp = AFIO->EXTICR[temp2] & ~(0xFU << (temp1 * 4U));
        temp |= portcode << (temp1 * 4U);
        AFIO->EXTICR[temp2] = temp;

        EXTI->IMR |= (1U << pin_number);
    }
}
void GPIO_DeInit(GPIO_Typedef_t *pGPIOx){
    if (pGPIOx == GPIOA)
    {
        GPIOA_RS_RCC();
    }
    else if (pGPIOx == GPIOB)
    {
        GPIOB_RS_RCC();
    }
    else if (pGPIOx == GPIOC)
    {
        GPIOC_RS_RCC();
    }
    else if (pGPIOx == GPIOD)
    {
        GPIOD_RS_RCC();
    }
    else if (pGPIOx == GPIOE)
    {
        GPIOE_RS_RCC();
    }
    else if (pGPIOx == GPIOF)
    {
        GPIOF_RS_RCC();
    }
    else if (pGPIOx == GPIOG)
    {
        GPIOG_RS_RCC();
    }
}
void GPIO_PeriClockControl(GPIO_Typedef_t *pGPIOx, uint8_t EnorDi){
    if (EnorDi == ENABLE)
    {
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
    }
    else
    {
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DIS();
        }
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DIS();
        }
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DIS();
        }
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DIS();
        }
        else if (pGPIOx == GPIOE)   
        {
            GPIOE_PCLK_DIS();
        }
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DIS();
        }
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_DIS();
        }    
    }

}
void GPIO_WriteToOutputPin(GPIO_Typedef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if (Value == GPIO_PIN_SET)
    {
        pGPIOx->BSRR = (1U << PinNumber);
    }
    else
    {
        pGPIOx->BSRR = (1U << (PinNumber + 16U));
    }
}
void GPIO_ToggleOutputPin(GPIO_Typedef_t *pGPIOx, uint8_t PinNumber){
    pGPIOx->ODR ^= (1 << PinNumber);
}
uint8_t GPIO_ReadFromInputPin(GPIO_Typedef_t *pGPIOx, uint8_t PinNumber){
    uint8_t value;
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi){
    if (EnorDi == ENABLE)
    {
        if (IRQNumber <= 31 )
        {
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
        else if (IRQNumber >= 96 && IRQNumber < 128)
        {
            *NVIC_ISER3 |= (1 << (IRQNumber % 96));
        }
        else if (IRQNumber >= 128 && IRQNumber < 160)
        {
            *NVIC_ISER4 |= (1 << (IRQNumber % 128));
        }
        else if (IRQNumber >= 160 && IRQNumber < 192)
        {
            *NVIC_ISER5 |= (1 << (IRQNumber % 160));
        }
        else if (IRQNumber >= 192 && IRQNumber < 224)
        {
            *NVIC_ISER6 |= (1 << (IRQNumber % 192));
        }
        else if (IRQNumber >= 224 && IRQNumber < 240)
        {
            *NVIC_ISER7 |= (1 << (IRQNumber % 224));
        }
    }
    else{
        if (IRQNumber <= 31 )
        {
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
        else if (IRQNumber >= 96 && IRQNumber < 128)
        {
            *NVIC_ICER3 |= (1 << (IRQNumber % 96));
        }
        else if (IRQNumber >= 128 && IRQNumber < 160)
        {
            *NVIC_ICER4 |= (1 << (IRQNumber % 128));
        }
        else if (IRQNumber >= 160 && IRQNumber < 192)
        {
            *NVIC_ICER5 |= (1 << (IRQNumber % 160));
        }
        else if (IRQNumber >= 192 && IRQNumber < 224)
        {
            *NVIC_ICER6 |= (1 << (IRQNumber % 192));
        }
        else if (IRQNumber >= 224 && IRQNumber < 240)
        {
            *NVIC_ICER7 |= (1 << (IRQNumber % 224));
        }
    }
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
    *(NVIC_IPR0 + iprx) |= (IRQPriority << shift_amount);
}

void GPIO_IRQHandling(uint8_t PinNumber){
    if (EXTI->PR & (1 << PinNumber))
    {
        EXTI->PR |= (1 << PinNumber);
    }
}
