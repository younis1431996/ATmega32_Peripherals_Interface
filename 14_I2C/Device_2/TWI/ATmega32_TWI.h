/*
 * ATmega32_TWI.h
 *
 *  Created on: Oct 15, 2021
 *      Author: Mahmoud Mohamed Younis.
 */

#ifndef TWI_ATMEGA32_TWI_H_
#define TWI_ATMEGA32_TWI_H_
/* inclusions */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "ATmega32_TWI_status.h"

/* Define bit rate */
#define TWI_SPEED   100

/* initialization */
void TWI_int(uint8_t address);

/* A.1.Master Write */
void TWI_master_write_byte(uint8_t __sla, uint8_t _byte);

/* A.2.Slave Read*/
void TWI_slave_read_byte(uint8_t *_byte);

/* B.1.Master Read */
void TWI_master_read_byte(uint8_t __sla, uint8_t *_byte);

/* B.2.Slave Write */
void TWI_slave_write_byte(uint8_t _byte);

#endif /* TWI_ATMEGA32_TWI_H_ */
