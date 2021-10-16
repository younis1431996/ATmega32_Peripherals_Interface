/*
 * ATmega32_TWI.cpp
 *
 *  Created on: Oct 15, 2021
 *      Author: Mahmoud Mohamed Younis
 */

/* inclusion */
#include "ATmega32_TWI.h"
#include "ATmega32_TWI_status.h"

/* >> 1.get TWI status */
//static char check_status_register(void){
//	 /* mask TWSR */
//	char twsr_value = TWSR & 0xF8;
//	return twsr_value;
//}

/* >> 2.check TWINT flag */
static bool check_TWINT_flag(void){
	return (bool)( (TWCR & (1<<TWINT)) >> TWINT);
}

/* >> 3.send start condition */
static void start_condition(void){
	/* A START condition is sent by writing the following value to TWCR */
	/* TWEN must be set to enable the Two-wire Serial Interface, TWSTA must be written to one to
	 * transmit a START condition and
	 * TWINT must be written to one to clear the TWINT Flag.
	 */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	/* wait until TWI finish */
	while( !(check_TWINT_flag()) );

	/* exit */
	return;
}

/* >> 4.send stop condition */
static void stop_condition(void){
	/* A STOP condition is sent by writing the following value to TWCR */
	/* TWEN must be set to enable the Two-wire Serial Interface, TWSTO must be written to one to
	 * transmit a STOP condition and
	 * TWINT must be written to one to clear the TWINT Flag.
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

	/* exit */
	return;
}

/* >> 5.send slave address + write */
static void master_send_slave_address_to_write(uint8_t address){
	/* write SLA + write bit */
	TWDR = ((address<<1)&(0xfe));

	/* clear interrupt flag to start operation */
	TWCR |= (1<<TWINT) | (1<<TWEN);

	/* wait until TWI finish */
	while( !(check_TWINT_flag()) );

	return;
}

/* >> 6.send slave address + read bit */
static void master_send_slave_address_to_read(char address){
	/* write SLA + read bit */
	TWDR = ((address<<1)|(0x01));

	/* clear interrupt flag to start operation */
	TWCR |= (1<<TWINT) | (1<<TWEN);

	/* wait until TWI finish */
	while( !(check_TWINT_flag()) );

	return;
}

/* initialization */
void TWI_int(uint8_t address){
#if TWI_SPEED == 100
	TWBR = 32;   // to set the speed 100kb/s  ,,, Speed 400khz TWBR=2;

#elif TWI_SPEED == 400
	TWBR = 2;   // to set the speed 100kb/s  ,,, Speed 400khz TWBR=2;
#endif

	/* PreScaler 1:1 */
	TWSR = 0;

	/* own slave address */
	TWAR=((address<<1)&(0xfe));

	/* exit */
}

/* <@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@> */

/* A.1.Master transmitter mode */
void TWI_master_write_byte(uint8_t __sla, uint8_t _byte){
	/* 1.send start condition */
	start_condition();

	/* 2.send slave address + write bit */
	master_send_slave_address_to_write(__sla);

	/* 3.master write byte */
	/* 3.1.writing the data byte to TWDR */
	TWDR = _byte;

	/* 3.2.the TWINT bit should be cleared (by writing it to one) to continue the transfer
	 *     enable TWI */
	TWCR |= (1<<TWINT) | (1<<TWEN);

	/* 3.3.wait until TWI finish */
	while( !(check_TWINT_flag()) );

	/* 4.send stop condition */
	stop_condition();

	/* 5.exit */
	return;
}

/* A.2.Slave read byte */
void TWI_slave_read_byte(uint8_t *_byte){
	/* 1.TWEN must be written to one to enable the TWI. The TWEA bit must be written to one to enable
       the acknowledgment of the device’s own slave address */
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);

	/* 2.After its own slave address and the write bit have been received, the TWINT Flag is set.
	     TWI waits until it is addressed by its own slave address */
	while( !(check_TWINT_flag()) );

	/* 3.Enable TWI, ACk for data receiving */
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);

	/* 4.wait until TWI finish */
	while( !(check_TWINT_flag()) );

	/* 5.Read TWDR */
	*_byte = TWDR;

	/* 6.exit */
	return;
}

/* <@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@>*<@> $ <@> */

/* B.1.Master Read */
void TWI_master_read_byte(uint8_t __sla, uint8_t *_byte){
	/* 1.send start condition */
	start_condition();

	/* 2.send slave address + read bit */
	master_send_slave_address_to_read(__sla);

	/* 3.master read byte */
	/* 3.1.the TWINT bit should be cleared (by writing it to one) to continue the transfer, enable TWI
	 *     and ACk pulse */
	TWCR |= (1<<TWEN) | (1<<TWINT) | (1<<TWEA);

	/* 3.2.wait until TWI finish */
	while( !(check_TWINT_flag()) );

	/* 3.3.read TWDR */
	*_byte = TWDR;

	/* 4.stop condition */
	stop_condition();

	/* 5.exit */
	return;
}

/* B.2.Slave Write */
void TWI_slave_write_byte(uint8_t _byte){
	/* 1.TWEN must be written to one to enable the TWI. The TWEA bit must be written to one to enable
       the acknowledgment of the device’s own slave address */
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);

	/* 2.After its own slave address and the write bit have been received, the TWINT Flag is set.
	     TWI waits until it is addressed by its own slave address */
	while( !(check_TWINT_flag()) );

	/* 3.salve write byte */
	/* 3.1.writing the data byte to TWDR */
	TWDR = _byte;

	/* 3.2.the TWINT bit should be cleared (by writing it to one) to continue the transfer
	 *     enable TWI */
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* 3.3.wait until TWI finish */
	while( !(check_TWINT_flag()) );

	/* 4.exit */
	return;
}
