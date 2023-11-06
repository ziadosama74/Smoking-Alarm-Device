/*
 * main.c
 *
 *  Created on: Nov 4, 2023
 *      Author: ziad osama
 */
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "CLCD_interface.h"
#include <util/delay.h>

int main(void)
{
	u16 Data ;
	DIO_voidSetPortDirection(DIO_u8PORTA,0b00001110);
	DIO_voidSetPinValue(DIO_u8PORTA,4,DIO_u8HIGH);
	DIO_voidSetPortDirection(DIO_u8PORTC,0b11111111);
	DIO_voidSetPortDirection(DIO_u8PORTD,0b00000111);
	ADC_voidInit();
	CLCD_voidInit();
	CLCD_voidSendString("Gas Value is:");
	CLCD_voidSetXYPosition(3,1);
	CLCD_voidSendString("NO SMOKING");
	while(1)
	{
		Data = ADC_u16ReadChannel(0);
		CLCD_voidSetXYPosition(13,0);
		CLCD_voidWriteInteger(Data);
		CLCD_voidSendString(" ");
		if (Data > 800)
		{
			DIO_voidSetPinValue(DIO_u8PORTA,1,DIO_u8HIGH);
			DIO_voidSetPinValue(DIO_u8PORTA,3,DIO_u8HIGH);
			DIO_voidSetPinValue(DIO_u8PORTA,2,DIO_u8LOW);
			CLCD_voidSetXYPosition(2,1);
			CLCD_voidSendString("SMOKING HERE");
			while(1)
			{
				Data = ADC_u16ReadChannel(0);
				CLCD_voidSetXYPosition(13,0);
				CLCD_voidWriteInteger(Data);
				CLCD_voidSendString(" ");
				if ( (DIO_U8_GetPinValue(DIO_u8PORTA,4)) == 0)
				{
					while((DIO_U8_GetPinValue(DIO_u8PORTA,4)) == 0);
					_delay_ms(2);
					DIO_voidSetPinValue(DIO_u8PORTA,1,DIO_u8LOW);
					DIO_voidSetPinValue(DIO_u8PORTA,3,DIO_u8LOW);
					DIO_voidSetPinValue(DIO_u8PORTA,2,DIO_u8HIGH);
					CLCD_voidClearLCD();
					CLCD_voidSendString("Gas Value is:");
					CLCD_voidSetXYPosition(3,1);
					CLCD_voidSendString("NO SMOKING");
					break;
				}
			}
		}
		else
		{
			DIO_voidSetPinValue(DIO_u8PORTA,2,DIO_u8HIGH);
			DIO_voidSetPinValue(DIO_u8PORTA,1,DIO_u8LOW);
			DIO_voidSetPinValue(DIO_u8PORTA,3,DIO_u8LOW);
		}
	}
}
