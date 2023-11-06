/*
 * DIO_interface.h
 *
 *  Created on: Aug 14, 2023
 *      Author: ziad osama
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_u8OUTPUT        1
#define DIO_u8INPUT         0

#define DIO_u8HIGH          1
#define DIO_u8LOW           0

#define DIO_u8PORTA         1
#define DIO_u8PORTB         2
#define DIO_u8PORTC         3
#define DIO_u8PORTD         4


void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin , u8 Copy_u8Direction);
void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin , u8 Copy_u8Value);
void DIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);
void DIO_void_SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);
u8 DIO_U8_GetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin);

#endif /* DIO_INTERFACE_H_ */
