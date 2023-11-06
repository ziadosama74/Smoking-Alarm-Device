/*
 * CLCD_confuge.h
 *
 *  Created on: Aug 16, 2023
 *      Author: ziad osama
 */

#ifndef CLCD_CONFUGE_H_
#define CLCD_CONFUGE_H_
/*
 * Options :
 *         1) DIO_u8PORTA
 *         2) DIO_u8PORTB
 *         3) DIO_u8PORTC
 *         4) DIO_u8PORTD
 */
#define CLCD_DATAPORT         DIO_u8PORTC
/*
 * Options :
 *         1) DIO_u8PORTA
 *         2) DIO_u8PORTB
 *         3) DIO_u8PORTC
 *         4) DIO_u8PORTD
 */
#define CLCD_CONTROLPORT      DIO_u8PORTD

#define CLCD_RS_PIN           0
#define CLCD_RW_PIN           1
#define CLCD_E_PIN            2
#endif /* CLCD_CONFUGE_H_ */
