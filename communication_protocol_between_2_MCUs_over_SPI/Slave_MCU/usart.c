/*
 * usart.c
 *
 *  Created on: Sep 27, 2021
 *      Author: TOSHIBA PC
 */

#include "usart.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the USART driver
 */

void UART_init(const Usart_ConfigType * Config_Ptr )
{
	uint32_t BAUD_PRESCALE;
	/* U2X = 1/0 for double transmission speed, Depending on the mode */
	UCSRA = ( (Config_Ptr->mode) << U2X );
	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0/1  Depending on the data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = 1<<RXEN | 1<< TXEN | (Config_Ptr->size & 0x04);
	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL) | ( (Config_Ptr->size & 0x03) << UCSZ0 ) | ( Config_Ptr->parity << UPM0)
			| ( (Config_Ptr->stop) << USBS )  ;
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/

	if(Config_Ptr->mode == ON)
	{
		BAUD_PRESCALE = F_CPU / ( ( Config_Ptr->baud_rate) * 8) - 1;
	}
	else if(Config_Ptr->mode == OFF)
	{
		BAUD_PRESCALE = F_CPU / ( ( Config_Ptr->baud_rate) * 16) - 1;
	}
	UBRRH= BAUD_PRESCALE>>8;
	UBRRL= BAUD_PRESCALE;
}
/*
 * Description : Function to send a byte using the USART driver
 */
void UART_sendByte(const uint16_t data)
{
	while( BIT_IS_CLEAR(UCSRA,UDRE) );
	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	UDR=data;
}
/*
 * Description : Function to send a nine bits data using the USART driver
 */
void UART_sendNineBitsData(const uint16_t data)
{
	while( BIT_IS_CLEAR(UCSRA,UDRE) );
	UCSRB = (UCSRB & 0xFE) | ( ( data & (0x0100) ) >>8 ) ;
	UDR = data;
}
/*
 * Description : Function to receive a byte using the USART driver
 */
uint8_t UART_receiveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	return UDR;

}
/*
 * Description : Function to send a string using the USART driver
 */
void UART_sendString(const uint8_t * Str)
{
	uint8_t i=0;
	while( Str[i]!='\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

/*
 * Description : Function to receive a string using the USART driver
 */
void UART_receiveString(uint8_t *Str)
{
	uint8_t i = 0;
	Str[i] = UART_receiveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}
	Str[i] = '\0';
}
