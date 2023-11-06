/*
 * CLCD_program.c
 *
 *  Created on: Aug 16, 2023
 *      Author: ziad osama
 */
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "CLCD_confuge.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "DIO_interface.h"
#include <util/delay.h>


void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*Set RS to 1 for data */
	DIO_voidSetPinValue(CLCD_CONTROLPORT,CLCD_RS_PIN,DIO_u8HIGH);
	/*Set RW to 0 for data */
	DIO_voidSetPinValue(CLCD_CONTROLPORT,CLCD_RW_PIN,DIO_u8LOW);
	/* Put The Data */
	DIO_void_SetPortValue(CLCD_DATAPORT,Copy_u8Data);
	/*Enable*/
	DIO_voidSetPinValue(CLCD_CONTROLPORT,CLCD_E_PIN,DIO_u8HIGH);
	/* delay*/
	_delay_ms(2);
	/* Display */
	DIO_voidSetPinValue(CLCD_CONTROLPORT,CLCD_E_PIN,DIO_u8LOW);
}


void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*Set RS to 0 for Command */
	DIO_voidSetPinValue(CLCD_CONTROLPORT,CLCD_RS_PIN,DIO_u8LOW);
	/*Set RW to 0 for Write */
	DIO_voidSetPinValue(CLCD_CONTROLPORT,CLCD_RW_PIN,DIO_u8LOW);
	/* Put The Data */
	DIO_void_SetPortValue(CLCD_DATAPORT,Copy_u8Command);
	/*Enable*/
	DIO_voidSetPinValue(CLCD_CONTROLPORT,CLCD_E_PIN,DIO_u8HIGH);
	/* delay*/
	_delay_ms(2);
	/* Display */
	DIO_voidSetPinValue(CLCD_CONTROLPORT,CLCD_E_PIN,DIO_u8LOW);
}


void CLCD_voidInit(void)
{
	_delay_ms(35);
	CLCD_voidSendCommand(0b00111000);
	CLCD_voidSendCommand(0b00001100);
	CLCD_voidSendCommand(0b00000001);
}
void CLCD_voidSendString(char*Copy_pCString)
{
	u8 Local_u8Iterator = 0;
	while(Copy_pCString[Local_u8Iterator]!='\0'){
		CLCD_voidSendData(Copy_pCString[Local_u8Iterator]);
		Local_u8Iterator++;
	}
}

void CLCD_voidSetXYPosition(u8 Copy_u8XPosition ,u8 Copy_u8YPosition)
{
	u8 Local_u8Address;
	if(Copy_u8YPosition == 0)
	{
		Local_u8Address = Copy_u8XPosition;
	}
	else if (Copy_u8YPosition == 1)
	{
		Local_u8Address = Copy_u8XPosition+0x40;
	}
	SET_BIT(Local_u8Address,7);
	CLCD_voidSendCommand(Local_u8Address);
}
void CLCD_voidClearLCD(void){
	CLCD_voidSendCommand(0b00000001);
}
void CLCD_voidWriteInteger(u16 Copy_u16Number)
{
	char Local_u8NumberStringArr[10];
	u8 Local_u8Temp , Local_u8ReverseIndex , Local_u8Iterator;
	u8 Local_u8StringIndex=0;

    /* Saving the Ascii of the integer number in string */
	while(Copy_u16Number>=10)
	{
		Local_u8NumberStringArr[Local_u8StringIndex]=Copy_u16Number%10 + 48;
		Local_u8StringIndex++;
		Copy_u16Number=Copy_u16Number/10;
	}
	Local_u8NumberStringArr[Local_u8StringIndex]=Copy_u16Number+48;
	Local_u8StringIndex++;

	/* To be String, not Array of characters */
	Local_u8NumberStringArr[Local_u8StringIndex]='\0';

    /* Reverse String */
	for (Local_u8ReverseIndex = 0, Local_u8Iterator = Local_u8StringIndex-1; Local_u8ReverseIndex < Local_u8Iterator; Local_u8ReverseIndex++, Local_u8Iterator--)
	{
		Local_u8Temp=Local_u8NumberStringArr[Local_u8ReverseIndex];
	    Local_u8NumberStringArr[Local_u8ReverseIndex]=Local_u8NumberStringArr[Local_u8Iterator];
	    Local_u8NumberStringArr[Local_u8Iterator]=Local_u8Temp;
	}

	/* Display the Integer */
	CLCD_voidSendString(Local_u8NumberStringArr);
}
void CLCD_voidWriteSpecialCharacter(u8 * Copy_pu8Pattern , u8 Copy_u8PatternNumber,u8 Copy_u8XPosition , u8 Copy_u8YPosition)
{

	u8 Local_u8CGRAMAddress=0;
	u8 Local_u8Iterator;

	/* Calculate CGRAM address where each block has 8 bytes */
	Local_u8CGRAMAddress=Copy_u8PatternNumber*8;

	/* Send CGRAM address to LCD, with setting bit 6 and clearing bit 7 */
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);

	/* Write the pattern in CGRAM */
	for (Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}

	/* Go back to DDRAM to display the pattern */
	CLCD_voidSetXYPosition(Copy_u8XPosition,Copy_u8YPosition);

	/* Display the pattern written in CGRAM */
	CLCD_voidSendData(Copy_u8PatternNumber);

}
