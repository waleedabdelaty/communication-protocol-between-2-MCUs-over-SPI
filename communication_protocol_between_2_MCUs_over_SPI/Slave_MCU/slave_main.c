/*
 * slave_main.c
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
	SPI_initSlave();
	uint8_t Str[256];
	while(1)
	{

		SPI_receiveString(Str);
		UART_sendString(Str);
		UART_sendByte(ENTER_ASCII);
	}
}

