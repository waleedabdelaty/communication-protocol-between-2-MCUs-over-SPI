/*
 * spi.h
 *
 *  Created on: Sep 27, 2021
 *      Author: TOSHIBA PC
 */


#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "spi_registers.h"
#include "dio.h"

typedef enum
{
	F_CPU_4,F_CPU_16,F_CPU_64,F_CPU_128,F_CPU_2,F_CPU_8,F_CPU_32
}EN_prescalar;

typedef struct
{
	EN_prescalar prescalar;

}ST_SPI_config_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void SPI_initMaster(ST_SPI_config_t* config);
void SPI_initSlave(void);
void SPI_sendByte(const uint8_t data);
uint8_t SPI_receiveByte(void);
void SPI_sendString(const uint8_t *Str);
void SPI_receiveString(uint8_t *Str);




#endif /* SPI_H_ */
