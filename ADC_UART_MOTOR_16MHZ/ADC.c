
/*
 * ADC.c
 *
 * Created: 6/3/2022 11:07:31 AM
 *  Author: islam
 */ 

#include "ADC.h"



#if    F_CPU     ==   16000000UL

uint8 Prescaler_Mode = 128;

#elif  F_CPU     ==   8000000UL

uint8 Prescaler_Mode = 64;

#elif  F_CPU     ==   1000000UL

uint8 Prescaler_Mode = 8;

#endif



void ADC_Init(){
	

	SET_BIT(ADMUX , 6); // Connecting AREFF to AVCC 5V

	///////////////////////////////////// PRESCALER CONFIGURATION ////////////////////////////////////
	/*
	#if  Prescaler_Mode == 8
	
	// Setting Prescaler to 8
	SET_BIT(ADCSRA , 0);
	SET_BIT(ADCSRA , 1);
	
	#endif
	
	
	#if Prescaler_Mode == 64 
	
	// Setting Prescaler to 64
	SET_BIT(ADCSRA , 1);
	SET_BIT(ADCSRA , 2);	
	
	
	#endif
	#if Prescaler_Mode == 128
	
	// Setting Prescaler to 128
	SET_BIT(ADCSRA , 0);
	SET_BIT(ADCSRA , 1);	
	SET_BIT(ADCSRA , 2);
		
	#endif
	*/
	
	// Setting Prescaler to 128
	SET_BIT(ADCSRA , 0);
	SET_BIT(ADCSRA , 1);
	SET_BIT(ADCSRA , 2);

	/////////////////////////////////////////////////////////////////////////	
	
	SET_BIT(ADCSRA , 7);  //-->Enable ADC
	
	SET_BIT(ADCSRA , 6);  //-->Pre-Conversion
	
}
uint16 Read_ADC(uint8 channel)
{

	//Select ADC Channel with SAFTEY MASK
	ADMUX &= 0xF0;
	
	//Channel Selection
	ADMUX |= channel;
	
	SET_BIT(ADCSRA , 6);  //-->Start_Conversion
	
	while(GET_BIT(ADCSRA , 6));
	//while(ADCSRA & (1<<ADSC));
	return ADC;

	
	
	
	
}
