/*
 * usart.h
 *
 *  Created on: Sep 27, 2021
 *      Author: TOSHIBA PC
 */

#ifndef USART_H_
#define USART_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "usart_registers.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	OFF,ON
}Usart_DoubleSpeedMode;

typedef enum
{
	FIVE,SIX,SEVEN,EIGHT,NINE=7
}Usart_CharacterSize;

typedef enum{
	DISABLED,EVEN=2,ODD=3
}Usart_ParityBit;

typedef enum{
	ONE,TWO
}Usart_StopBit;

typedef struct{
	Usart_DoubleSpeedMode mode;
	Usart_CharacterSize size;
	Usart_ParityBit parity;
	Usart_StopBit stop;
	uint32_t baud_rate;

}Usart_ConfigType;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the USART driver
 */

void UART_init(const Usart_ConfigType * Config_Ptr );
/*
 * Description : Function to send a byte using the USART driver
 */
void UART_sendByte(const uint16_t data);
/*
 * Description : Function to send a nine bits data using the USART driver
 */
void UART_sendNineBitsData(const uint16_t data);
/*
 * Description : Function to receive a byte using the USART driver
 */
uint8_t UART_receiveByte(void);
/*
 * Description : Function to send a string using the USART driver
 */
void UART_sendString(const uint8_t * Str);
/*
 * Description : Function to receive a string using the USART driver
 */
void UART_receiveString(uint8_t *Str);

#endif /* USART_H_ */
