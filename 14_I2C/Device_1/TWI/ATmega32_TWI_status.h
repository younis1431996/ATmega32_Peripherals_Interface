/*
 * ATmega32_TWI_status.h
 *
 *  Created on: Oct 15, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef TWI_ATMEGA32_TWI_STATUS_H_
#define TWI_ATMEGA32_TWI_STATUS_H_

/* 1.master transmitter mode */

// >> 1.1.MT_START_condition_has_been_transmitted
#define MT_STA_ (0x08)

// >> 1.2.MT_Repeated_START_condition_has_been_transmitted
#define MT_R_STA_ (0x10)

// >> 1.3.MT_SLA_and_W_has_been_transmitted_ACK_has_been_received
#define MT_SLA_plus_W_with_ACk_ (0x18)

// >> 1.4.MT_SLA_and_W_has_been_transmitted_ACK_not_has_been_received
#define MT_SLA_plus_W_not_Ack_ (0x20)

// >> 1.5.MT_Data_byte_has_been_transmitted_ACK_has_been_received
#define MT_data_with_ACk_ (0x28)

// >> 1.6.MT_Data_byte_has_been_transmitted_ACK_not_has_been_received
#define MT_Data_not_ACk_ (0x30)

//>> 1.7.MT_Arbitration_lost_in_SLA_and_W_OR_data_bytes
#define MT_ARBT_lost_ (0x38)

/*-------------------------------------------------------------------------------------------------------*/

/* 2.slave receiver mode */
// >> 2.1 Own SLA+W has been received; ACK has been returned.
#define SR_SLA_pluse_W_with_ACK (0x60)

// >> 2.2 Arbitration lost in SLA+R/W as master; own SLA+W has been received; ACK has been returned.
#define SR_ARBT_lost_SLA_plus_W_with_ACK (0x68)

// >> 2.3 General call address has been received; ACK has been returned.
#define SR_generall_coll_with_ACK (0x70)

// >> 2.4 Arbitration lost in SLA+R/W as master; General call address has been received; ACK has been returned.
#define SR_ARBT_lost_generall_call_with_ACK (0x78)

// >> 2.5 Previously addressed with own SLA+W; data has been received; ACK has been returned.
#define SR_data_with_ACk (0x80)

// >> 2.6 Previously addressed with own SLA+W; data has been received; NOT ACK has been returned.
#define SR_data_with_not_ACk (0x88)

// >> 2.7 Previously addressed with general call; data has been received; ACK has been returned.
#define SR_data_generall_call_with_ACk (0x90)

// >> 2.8 Previously addressed with general call; data has been received; NOT ACK has been returned
#define SR_data_generall_call_not_ACk (0x98)

// >> 2.9 A STOP condition or repeated START condition has been received while still addressed as slave
#define SR_STO_or_RSTA (0x0A)

/*-------------------------------------------------------------------------------------------------------*/


#endif /* TWI_ATMEGA32_TWI_STATUS_H_ */
