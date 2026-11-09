/*
 * stm32_SPI.c
 *
 *  Created on: Nov 6, 2026
 *      Author: theng
 */
#include "stm32_SPI.h"

/* SPI APIs */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    // Implementation for SPI initialization
    SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

    // __vo uint8_t SPI_Device_Mode;
    // __vo uint8_t SPI_Bus_Config;
    // __vo uint8_t SPI_SclkSpeed;
    // __vo uint8_t SPI_DFF;
    // __vo uint8_t SPI_SSM;
    // __vo uint8_t SPI_CPOL;
    // __vo uint8_t SPI_CPHA;
//    uint8_t temp = 0U;
//    uint8_t device_mode = pSPIHandle->pSPI_Config->SPI_Device_Mode;
//    uint8_t bus_config = pSPIHandle->pSPI_Config->SPI_Bus_Config;
//    uint8_t sclk_speed = pSPIHandle->pSPI_Config->SPI_SclkSpeed;


}

void SPI_DeInit(SPI_Typedef_t *pSPIx)
{
    // Implementation for SPI de-initialization
}

void SPI_PeriClockControl(SPI_Typedef_t *pSPIx, uint8_t EnorDi)
{
    // Implementation for SPI peripheral clock control
    if (EnorDi == ENABLE)
    {
        if (pSPIx == SPI1)
        {
            SPI1_PCLK_EN();
        }
        else if (pSPIx == SPI2)
        {
            SPI2_PCLK_EN();
        }
        else if (pSPIx == SPI3)
        {
            SPI3_PCLK_EN();
        }      
    }
    else
    {
        if (pSPIx == SPI1)
        {
            SPI1_PCLK_DIS();
        }
        else if (pSPIx == SPI2)
        {
            SPI2_PCLK_DIS();
        }
        else if (pSPIx == SPI3)
        {
            SPI3_PCLK_DIS();
        }      
    }
}

uint16_t SPI_SendData(SPI_Handle_t *pSPIHandle, uint16_t data)
{
    // Implementation for sending data over SPI
    return 0; // Placeholder return value
}
uint16_t SPI_ReceiveData_IT(SPI_Handle_t *pSPIHandle, uint16_t data)
{
    // Implementation for receiving data over SPI using interrupts
    return 0; // Placeholder return value
}

void SPI_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)  
{
    // Implementation for configuring SPI interrupts
}

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    // Implementation for configuring SPI interrupt priority
}

void SPI_IRQHandling(uint8_t PinNumber)
{
    // Implementation for handling SPI interrupts
}
