/*
 * CLCD_interface.h
 *
 *  Created on: Aug 16, 2023
 *      Author: ziad osama
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_


void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidInit(void);
void CLCD_voidSendString(char*Copy_pCString);
void CLCD_voidSetXYPosition(u8 Copy_u8XPosition ,u8 Copy_u8YPosition);
void CLCD_voidClearLCD(void);


#endif /* CLCD_INTERFACE_H_ */
