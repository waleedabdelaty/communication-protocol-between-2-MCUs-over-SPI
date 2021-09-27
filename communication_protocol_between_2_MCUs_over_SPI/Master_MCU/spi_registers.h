/*
 * spi_registers.h
 *
 *  Created on: Sep 27, 2021
 *      Author: TOSHIBA PC
 */

#ifndef SPI_REGISTERS_H_
#define SPI_REGISTERS_H_

#define SPCR            (*(volatile uint8_t*)(0x2D))
#define SPDR            (*(volatile uint8_t*)(0x2F))
#define SPSR            (*(volatile uint8_t*)(0x2E))


#define SPE   6
#define MSTR  4
#define SPIF  7




#endif /* SPI_REGISTERS_H_ */
