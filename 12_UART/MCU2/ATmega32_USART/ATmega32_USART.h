/*
 * ATmega32_USART.h
 *
 *  Created on: Oct 11, 2021
 *      Author: Mahmoud Mohamed Younis.
 */

#ifndef ATMEGA32_USART_ATMEGA32_USART_H_
#define ATMEGA32_USART_ATMEGA32_USART_H_

/* inclusions */
#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>

#define F_CPU 	8000000UL
#define BAUD_PRESCALE(USART_BAUDRATE) ( (F_CPU / (USART_BAUDRATE * 16UL)) - 1)


/* USART functions */
// 1.baud rate initialize.
void ATmega32_USART_baud_rate_init(long baud_rate);

// 2.enable Receiver.
void ATmega32_USART_RX_enable(void);

// 3.disable Receiver.
void ATmega32_USART_RX_disable(void);

// 4.enable transmitter.
void ATmega32_USART_TX_enable(void);

// 5.disable transmitter.
void ATmega32_USART_TX_disable(void);

// 6.set character size.
void ATmega32_USART_char_size(uint8_t __size);

// 7.receive character.
void ATmega32_USART_receive_char(char *character);

// 8.receive string.
void ATmega32_USART_receive_str(char *character);

// 9.transmit character.
void ATmega32_USART_transmit_char(char character);

// 10.transmit string.
void ATmega32_USART_transmit_str(char character[]);

// 11.new line.
void ATmega32_USART_print_new_line(void);

// 12.Enable synchronous mode.
void ATmega32_USART_sync_mode_enable(void);

// 13.Disable synchronous mode.
void ATmega32_USART_sync_mode_disable(void);

#endif /* ATMEGA32_USART_ATMEGA32_USART_H_ */
