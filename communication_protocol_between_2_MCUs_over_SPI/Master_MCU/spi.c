/*
 * spi.c
 *
 *  Created on: Sep 27, 2021
 *      Author: TOSHIBA PC
 */



#include "spi.h"
#define ENTER_ASCII 13
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void SPI_initMaster(ST_SPI_config_t* config)
{
	EN_prescalar prescalar = config->prescalar;
	SPCR |= (prescalar & 0x03);

	if (prescalar >= 4) /*SPI2X = 1 */
	{
		SPSR |= 1<<0;
	}
	SET_BIT(DDRB,4 );
	SET_BIT(DDRB,5 );
	CLEAR_BIT(DDRB,6 );
	SET_BIT(DDRB,7 );

	SPCR |= (1<<SPE)|(1<<MSTR); // enable SPI + enable Master + choose SPI clock = Fosc/4
}

void SPI_initSlave(void)
{
	CLEAR_BIT(DDRB,4 );
	CLEAR_BIT(DDRB,5 );
	SET_BIT(DDRB,6 );
	CLEAR_BIT(DDRB,7 );
	SPCR = 1<<SPE ; // enable SPI + choose SPI clock = Fosc/4
}

void SPI_sendByte(const uint8_t data)
{
	SPDR=data;
	while(BIT_IS_CLEAR(SPSR,SPIF));
}
uint8_t SPI_receiveByte(void)
{
	while(BIT_IS_CLEAR(SPSR,SPIF));
	return SPDR;
}

void SPI_sendString(const uint8_t * Str)
{
	while(*Str != '\0')
	{
		SPI_sendByte(*Str);
		Str++;
	}
}

void SPI_receiveString(uint8_t *Str)
{
	uint8_t i=0;
	Str[i]=SPI_receiveByte();
	while ( Str[i] != ENTER_ASCII)
	{
		i++;
		Str[i]=SPI_receiveByte();
	}
	Str[i]='\0';
}
