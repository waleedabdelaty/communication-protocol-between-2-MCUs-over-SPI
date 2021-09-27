/*
 * master_main.c
 *
 *  Created on: Sep 27, 2021
 *      Author: TOSHIBA PC
 */


#include "spi.h"
#include "usart.h"
#define ENTER_ASCII 13
int main(void)
{
	/*UART INIT*/
	Usart_ConfigType usart_config = {ON,EIGHT,DISABLED,ONE,9600};
	UART_init(&usart_config);

	/*SPI INIT*/
	ST_SPI_config_t spi_config  = {F_CPU_4};
	SPI_initMaster(&spi_config);

	uint8_t Str[300];
	uint8_t index;
	while(1)
	{
		index = 0;
		UART_receiveString(Str);
		while (Str[index] != '\0'){index++;}
		if(index > 256)
		{
			SPI_sendString("Number of Char Must Be <= 256");
			SPI_sendByte(ENTER_ASCII);
		}
		else
		{
			Str[index] = ENTER_ASCII ;
			Str[index+1] = '\0';
			SPI_sendString(Str);
		}


	}
}

