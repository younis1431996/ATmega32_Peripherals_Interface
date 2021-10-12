/*
 * ATmega32_USART.cpp
 *
 *  Created on: Oct 11, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions */
#include "ATmega32_USART.h"

// 1.baud rate initialize.
void ATmega32_USART_baud_rate_init(long baud_rate){
	/* Load lower 8-bits of the baud rate */
	UBRRL = BAUD_PRESCALE(baud_rate);

	/* Load upper 8-bits*/
	UBRRH = (BAUD_PRESCALE(baud_rate) >> 8);
}

// 2.enable Receiver.
void ATmega32_USART_RX_enable(void){
	UCSRB |= (1 << RXEN);
}

// 3.disable Receiver.
void ATmega32_USART_RX_disable(void){
	UCSRB &= ~(1 << RXEN);
}

// 4.enable transmitter.
void ATmega32_USART_TX_enable(void){
	UCSRB |= (1 << TXEN);
}

// 5.disable transmitter.
void ATmega32_USART_TX_disable(void){
	UCSRB &= ~(1 << TXEN);
}

// 6.set character size.
void ATmega32_USART_char_size(uint8_t __size){
	// The URSEL must be one when writing the UCSRC.
	UCSRC |= (1<<URSEL);

	if(__size == 5){
		UCSRC &= ~(1<<UCSZ0);
		UCSRC &= ~(1<<UCSZ1);
		UCSRB &= ~(1<<UCSZ2);
		return;
	}else if(__size == 6){
		UCSRC |=  (1<<UCSZ0);
		UCSRC &= ~(1<<UCSZ1);
		UCSRB &= ~(1<<UCSZ2);
		return;
	}else if(__size == 7){
		UCSRC &= ~(1<<UCSZ0);
		UCSRC |=  (1<<UCSZ1);
		UCSRB &= ~(1<<UCSZ2);
		return;
	}else if(__size == 8){
		UCSRC |=  (1<<UCSZ0);
		UCSRC |=  (1<<UCSZ1);
		UCSRB &= ~(1<<UCSZ2);
		return;
	}else if(__size == 9){
		UCSRC |=  (1<<UCSZ0);
		UCSRC |=  (1<<UCSZ1);
		UCSRB |=  (1<<UCSZ2);
		return;
	}
}

/* Function to check the state of a bit if one or zero. */
static bool bit_check(volatile uint8_t *reg, uint8_t bit){
	return ( ( *reg&(1<<bit) ) >> bit );
}

// 7.receive character.
void ATmega32_USART_receive_char(char *character){
	/* Wait till data is received */
	while (bit_check(&UCSRA, RXC) == 0);

	/* Return the byte */
	*character = UDR;
}

// 8.receive string.
void ATmega32_USART_receive_str(char *str){
	int i=0;
	do{
		ATmega32_USART_receive_char(&str[i]);
		i++;
	}while(str[i]!='\0');
}

// 9.transmit character.
void ATmega32_USART_transmit_char(char character){
	/* Wait for empty transmit buffer */
	while (! (bit_check(&UCSRA, UDRE)) );

	/* send character*/
	UDR = character;
}

// 10.transmit string.
void ATmega32_USART_transmit_str(char str[]){
	for(int i=0; str[i]!='\0'; i++){
		ATmega32_USART_transmit_char(str[i]);
	}
	return;
}

// 11.new line.
void ATmega32_USART_print_new_line(void){
	ATmega32_USART_transmit_char('\r');
}


// 12.Enable synchronous mode.
void ATmega32_USART_sync_mode_enable(void){
	UCSRC |= (1<<URSEL) | (1<<UMSEL);
}

// 13.Disable synchronous mode.
void ATmega32_USART_sync_mode_disable(void){
	UCSRC |= (1<<URSEL);
	UCSRC &= ~(1<<UMSEL);
}
