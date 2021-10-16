/*
 * EEPROM.h
 *
 *  Created on: Oct 16, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef EEPROM_EEPROM_H_
#define EEPROM_EEPROM_H_

/* inclusions */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void EEPROM_write(uint16_t __add, uint8_t __byte){
	/* 1.Wait for completion of previous write */
	while(EECR & (1<<EEWE));

	/* 2.Set up address and data registers */
	EEAR = __add;
	EEDR = __byte;

	/* 3.Write logical one to EEMWE */
	EECR |= (1<<EEMWE);

	/* 4.Start EEPROM write by setting EEWE */
	EECR |= (1<<EEWE);

	/* 5.exit */
	return;
}

void EEPROM_read(uint16_t __add, uint8_t *__byte){
	/* 1.Wait for completion of previous write */
	while(EECR & (1<<EEWE));

	/* 2.Set up address register */
	EEAR = __add;

	/* 3.Start EEPROM read by writing EERE */
	EECR |= (1<<EERE);

	/* 4.Return data from data register */
	*__byte = EEDR;

	/* 5.exit */
	return;
}

#endif /* EEPROM_EEPROM_H_ */
