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
    if (pGPIOHandle->pGPIOx->GPIO_Pin_Mode <= GPIO_MODE_OUTPUT)
    {
        if (pGPIOHandle->pGPIOx->GPIO_Pin_Number <=7)
        {
            temp = (pGPIOHandle->pGPIO_Config->CRL & ~(0xF << (4 * pGPIOHandle->pGPIOx->GPIO_Pin_Number)));
            temp |= (pGPIOHandle->pGPIOx->GPIO_Pin_Mode << (4 * pGPIOHandle->pGPIOx->GPIO_Pin_Number));
            pGPIOHandle->pGPIO_Config->CRL = temp;
            temp = (pGPIOHandle->pGPIO_Config->CRL & ~(0xF << ((4 * pGPIOHandle->pGPIOx->GPIO_Pin_Number) + 2)));
            temp |= (pGPIOHandle->pGPIOx->GPIO_Pin_Speed << ((4 * pGPIOHandle->pGPIOx->GPIO_Pin_Number) + 2));
            pGPIOHandle->pGPIO_Config->CRL = temp;
            
        }
        else
        {
            temp = (pGPIOHandle->pGPIO_Config->CRH & ~(0xF << (4 * (pGPIOHandle->pGPIOx->GPIO_Pin_Number))));
            temp |= (pGPIOHandle->pGPIOx->GPIO_Pin_Mode << (4 * (pGPIOHandle->pGPIOx->GPIO_Pin_Number)));
            pGPIOHandle->pGPIO_Config->CRH = temp;
            temp = (pGPIOHandle->pGPIO_Config->CRH & ~(0xF << ((4 * (pGPIOHandle->pGPIOx->GPIO_Pin_Number)) + 2)));
            temp |= (pGPIOHandle->pGPIOx->GPIO_Pin_Speed << ((4 * (pGPIOHandle->pGPIOx->GPIO_Pin_Number)) + 2));
            pGPIOHandle->pGPIO_Config->CRH = temp;
        }
    }
    else if (pGPIOHandle->pGPIOx->GPIO_Pin_Mode == GPIO_MODE_AF)
    {
        /* code */
    }
    else
    {
        if (pGPIOHandle->pGPIOx->GPIO_Pin_Mode == GPIO_MODE_IT_FT)
        {
            EXTI->FTSR |= (1<< pGPIOHandle->pGPIOx->GPIO_Pin_Number);       // Enable falling edge trigger
            EXTI->RTSR &= ~(1<< pGPIOHandle->pGPIOx->GPIO_Pin_Number);      // Disable rising edge trigger
        }
        else if (pGPIOHandle->pGPIOx->GPIO_Pin_Mode == GPIO_MODE_IT_RT)
        {
            EXTI->FTSR &= ~(1<< pGPIOHandle->pGPIOx->GPIO_Pin_Number);       // Disable falling edge trigger
            EXTI->RTSR |= (1<< pGPIOHandle->pGPIOx->GPIO_Pin_Number);       // Enable rising edge trigger
        }
        else if (pGPIOHandle->pGPIOx->GPIO_Pin_Mode == GPIO_MODE_IT_RFT)
        {
            EXTI->FTSR |= (1<< pGPIOHandle->pGPIOx->GPIO_Pin_Number);      // Enable falling edge trigger
            EXTI->RTSR |= (1<< pGPIOHandle->pGPIOx->GPIO_Pin_Number);       // Enable rising edge trigger  
        }
        uint8_t portcode = GPIO_BASEADR_TO_NUMPIN(pGPIOHandle->pGPIOx);
        uint8_t temp1 = (pGPIOHandle->pGPIOx->GPIO_Pin_Number % 4);
        uint8_t temp2 = (pGPIOHandle->pGPIOx->GPIO_Pin_Number / 4);
        AFIO->EXTICR[temp2] = portcode << (temp1 * 4);                  // Configure the EXTI line to the corresponding GPIO port
        EXTI->IMR |= (1<< pGPIOHandle->pGPIOx->GPIO_Pin_Number);       // Enable interrupt mask
    }
}
void GPIO_DeInit(GPIO_TypeDef_t *pGPIOx){
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
void GPIO_PeriClockControl(GPIO_TypeDef_t *pGPIOx, uint8_t EnorDi){
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
void GPIO_WriteToOutputPin(GPIO_Config_t *pPinConfig, uint8_t PinNumber, uint8_t Value)
{
    if (Value == GPIO_PIN_SET)
    {
        pPinConfig->BSRR = (1U << PinNumber);
    }
    else
    {
        pPinConfig->BSRR = (1U << (PinNumber + 16U));
    }
}
void GPIO_ToggleOutputPin(GPIO_Config_t *pPinConfig, uint8_t PinNumber){
    pPinConfig->ODR ^= (1 << PinNumber);
}
uint8_t GPIO_ReadFromInputPin(GPIO_Config_t *pPinConfig, uint8_t PinNumber){
    uint8_t value;
    value = (uint8_t)((pPinConfig->IDR >> PinNumber) & 0x00000001);
	return value;
}
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi){

}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){

}
