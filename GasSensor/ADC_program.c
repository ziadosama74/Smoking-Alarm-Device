/*
 * ADC_program.c
 *
 *  Created on: Aug 29, 2023
 *      Author: ziad osama
 */
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_confuge.h"
#include "ADC_private.h"
#include "ADC_interface.h"
#include "ADC_register.h"
void ADC_voidInit(void)
{
	/* SET VREF */
	#if (VREF == AREF)
		CLEAR_BIT(ADMUX,7);
		CLEAR_BIT(ADMUX,6);
	#elif(VREF == AVCC)
		CLEAR_BIT(ADMUX,7);
		SET_BIT(ADMUX,6);
	#elif(VREF == INT_2_56)
		SET_BIT(ADMUX,7);
		SET_BIT(ADMUX,6);
	#endif
	/* NORMAL ADJUSTMENT */
	CLEAR_BIT(ADMUX,5);
	/* SELESCT PRESCALER : DIVIDE BY 2 */
	CLEAR_BIT(ADCSRA,2);
	CLEAR_BIT(ADCSRA,1);
	CLEAR_BIT(ADCSRA,0);
	/* ENABLE ADC */
	SET_BIT(ADCSRA,7);
}
u16 ADC_u16ReadChannel(u8 Copy_u8Channel)
{
	/* SELECT CHANNEL */
	ADMUX &= 0b11100000;
	ADMUX |= Copy_u8Channel;
	/* START CONVERSION */
	SET_BIT(ADCSRA,6);
	/* POLING ON THE ADC FLAG */
	while((GET_BIT(ADCSRA,4))!= 1)
	{
		asm("NOP");
	}
	/* CLEAR ADC FLAG */
	SET_BIT(ADCSRA,4);
	/* RETURN THE DIGITAL FLAG */
	return ADC;
}
