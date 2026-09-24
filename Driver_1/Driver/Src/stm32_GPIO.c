/*
 * stm32_GPIO.c
 *
 *  Created on: Sep 7, 2026
 *      Author: theng
 */

#include "stm32_GPIO.h"

void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);
    
    uint32_t temp = 0;
    if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode <= GPIO_MODE_OUTPUT)
    {
        if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Number <=7)
        {
            temp = (pGPIOHandle->pGPIOx->CRL & ~(0xF << (4 * pGPIOHandle->pGPIO_Config->GPIO_Pin_Number)));
            temp |= (pGPIOHandle->pGPIO_Config->GPIO_Pin_Speed << (4 * pGPIOHandle->pGPIO_Config->GPIO_Pin_Number));
            pGPIOHandle->pGPIOx->CRL = temp;
            temp = (pGPIOHandle->pGPIOx->CRL & ~(0xF << ((4 * pGPIOHandle->pGPIO_Config->GPIO_Pin_Number) + 2)));
            temp |= (pGPIOHandle->pGPIO_Config->GPIO_Type << ((4 * pGPIOHandle->pGPIO_Config->GPIO_Pin_Number) + 2));
            pGPIOHandle->pGPIOx->CRL = temp;
        }
        else
        {
            temp = (pGPIOHandle->pGPIOx->CRH & ~(0xF << (4 * (pGPIOHandle->pGPIO_Config->GPIO_Pin_Number))));
            temp |= (pGPIOHandle->pGPIO_Config->GPIO_Pin_Speed << (4 * (pGPIOHandle->pGPIO_Config->GPIO_Pin_Number)));
            pGPIOHandle->pGPIOx->CRH = temp;
            temp = (pGPIOHandle->pGPIOx->CRH & ~(0xF << ((4 * (pGPIOHandle->pGPIO_Config->GPIO_Pin_Number)) + 2)));
            temp |= (pGPIOHandle->pGPIO_Config->GPIO_Type << ((4 * (pGPIOHandle->pGPIO_Config->GPIO_Pin_Number)) + 2));
            pGPIOHandle->pGPIOx->CRH = temp;
        }
    }
    else
    {
        SYSCFG_PCLK_EN();
        if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_FT)
        {
            EXTI->FTSR |= (1<< pGPIOHandle->pGPIO_Config->GPIO_Pin_Number);       // Enable falling edge trigger
            EXTI->RTSR &= ~(1<< pGPIOHandle->pGPIO_Config->GPIO_Pin_Number);      // Disable rising edge trigger
        }
        else if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_RT)
        {
            EXTI->FTSR &= ~(1<< pGPIOHandle->pGPIO_Config->GPIO_Pin_Number);       // Disable falling edge trigger
            EXTI->RTSR |= (1<< pGPIOHandle->pGPIO_Config->GPIO_Pin_Number);       // Enable rising edge trigger
        }
        else if (pGPIOHandle->pGPIO_Config->GPIO_Pin_Mode == GPIO_MODE_IT_RFT)
        {
            EXTI->FTSR |= (1<< pGPIOHandle->pGPIO_Config->GPIO_Pin_Number);      // Enable falling edge trigger
            EXTI->RTSR |= (1<< pGPIOHandle->pGPIO_Config->GPIO_Pin_Number);       // Enable rising edge trigger  
        }
        uint8_t portcode = GPIO_BASEADR_TO_NUMPIN(pGPIOHandle->pGPIOx);
        uint8_t temp1 = (pGPIOHandle->pGPIO_Config->GPIO_Pin_Number % 4);
        uint8_t temp2 = (pGPIOHandle->pGPIO_Config->GPIO_Pin_Number / 4);
        AFIO->EXTICR[temp2] = portcode << (temp1 * 4);                  // Configure the EXTI line to the corresponding GPIO port
        EXTI->IMR |= (1<< pGPIOHandle->pGPIO_Config->GPIO_Pin_Number);       // Enable interrupt mask
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
