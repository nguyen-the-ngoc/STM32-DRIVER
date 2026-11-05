/*
 * stm32_SPI.h
 *
 *  Created on: Nov 6, 2026
 *      Author: theng
 */

#ifndef INC_STM32_SPI_H_
#define INC_STM32_SPI_H_
#include "stm32_103.h"

/* SPI Configuration Device */
#define SPI_MODE_MASTER		0
#define SPI_MODE_SLAVE		1

typedef struct
{
    __vo uint8_t SPI_Device_Mode;
    __vo uint8_t SPI_Bus_Config;
    __vo uint8_t SPI_SclkSpeed;
    __vo uint8_t SPI_DFF;
    __vo uint8_t SPI_CPOL;
    __vo uint8_t SPI_CPHA;
    __vo uint8_t SPI_SSM;
}SPI_Config_t;

typedef struct
{
    SPI_Typedef_t *pSPIx;
    SPI_Config_t *pSPI_Config;
}SPI_Handle_t;


#endif /* INC_STM32_SPI_H_ */
