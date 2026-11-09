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

/* SPI Bus Configuration */
#define SPI_BUS_CONFIG_FULL_DUPLEX		0
#define SPI_BUS_CONFIG_HALF_DUPLEX		1
#define SPI_BUS_CONFIG_SIMPLEX_RX		2
#define SPI_BUS_CONFIG_SIMPLEX_TX		3

/* SPI SCLK Speed */
#define SPI_SCLK_SPEED_DIV2		    0
#define SPI_SCLK_SPEED_DIV4		    1
#define SPI_SCLK_SPEED_DIV8		    2
#define SPI_SCLK_SPEED_DIV16		3
#define SPI_SCLK_SPEED_DIV32		4
#define SPI_SCLK_SPEED_DIV64		5
#define SPI_SCLK_SPEED_DIV128		6
#define SPI_SCLK_SPEED_DIV256		7

/* SPI Data Frame Format */
#define SPI_DFF_8BIT		0
#define SPI_DFF_16BIT		1

/* SPI Software Slave Management */
#define SPI_SSM_DI			0
#define SPI_SSM_EN			1

/* SPI Clock Polarity and Phase */
#define SPI_CPOL_LOW		0
#define SPI_CPOL_HIGH		1

/* SPI Clock Phase */
#define SPI_CPHA_FIRST_EDGE	0
#define SPI_CPHA_SECOND_EDGE	1

typedef struct
{
    __vo uint8_t SPI_Device_Mode;
    __vo uint8_t SPI_Bus_Config;
    __vo uint8_t SPI_SclkSpeed;
    __vo uint8_t SPI_DFF;
    __vo uint8_t SPI_SSM;
    __vo uint8_t SPI_CPOL;
    __vo uint8_t SPI_CPHA;
}SPI_Config_t;

typedef struct
{
    SPI_Typedef_t *pSPIx;
    SPI_Config_t *pSPI_Config;
}SPI_Handle_t;

/* SPI APIs */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_Typedef_t *pSPIx);
void SPI_PeriClockControl(SPI_Typedef_t *pSPIx, uint8_t EnorDi);

uint16_t SPI_SendData(SPI_Handle_t *pSPIHandle, uint16_t data);
uint16_t SPI_ReceiveData_IT(SPI_Handle_t *pSPIHandle, uint16_t data);

void SPI_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32_SPI_H_ */
