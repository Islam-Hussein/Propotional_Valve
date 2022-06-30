/*
 * ENCODER.c
 *
 * Created: 09.02.2022 09:20:17
 *  Author: student
 */ 
#include "ENCODER.h"
#include "ENC_Cfg.h"
#include <util/delay.h>

extern No_of_Readings;
extern arr;

	
#if ENC_MODE == 12

const float step = 11.375;

#elif ENC_MODE == 10

const float step = 2.841666667;

#endif

	

void ENC_Init()
{
	DIO_SetPinDir(ENC_PORT , DO , DIO_PIN_INPUT );
	DIO_SetPinDir(ENC_PORT , Clk, DIO_PIN_OUTPUT);
	DIO_SetPinDir(ENC_PORT , CS, DIO_PIN_OUTPUT);
	
	_delay_us(1);

}

uint16 ENC_Read(void)
{
	uint16 ANGLE = 0;
	

	DIO_SetPinValue(ENC_PORT , CS, DIO_PIN_LOW );
	_delay_us(1);
	
	
	for (uint8 i = 0;  i < ENC_MODE ; i++) 
	{

		DIO_SetPinValue(ENC_PORT , Clk, DIO_PIN_LOW );
		_delay_us(1);
		DIO_SetPinValue(ENC_PORT , Clk, DIO_PIN_HIGH );
		_delay_us(1);	
		
		ANGLE = (ANGLE << 1) | GET_BIT(PIND,DO);
	}
	
	DIO_SetPinValue(ENC_PORT , CS, DIO_PIN_HIGH );
	
	return ANGLE;	
}

uint16 ENC_Read_In_Degree(void)   //--> Output is a degree between 0 and 360
{
	uint16 degree = 0;
	
	degree = (uint16)((float)ENC_Read() / step) ;

	//degree = (uint16)((float)ENC_Read_avg() / step) ;
	return (uint16)degree;
}

uint16 ENC_Deg_to_Bit(uint16 Degree) //--> Output is degree but in Bits between 0 and 2^ENC_MODE -1
{
	uint16 Deg_in_Bits  = 0;
	Deg_in_Bits  = (uint16)((float)Degree / step) ;
	
	return Deg_in_Bits;
}



uint16 ENC_Read_avg(uint16 *Arr_of_Readings)
{
	int Max = 0 , Min = (2 ^ ENC_MODE) -1;
	for (int i = 0 ; i < 50 ; i++)
	{
		if (*Arr_of_Readings > Max)
		{
			Max = *Arr_of_Readings;
		}
		if (*Arr_of_Readings < Min)
		{
			Min = *Arr_of_Readings;
		}
		*Arr_of_Readings++;
	}
	return ((Min+Max) / 2);
}


void Arr_Of_Readings(uint16 *ARR)
{
	for (int i = 0 ; i < 50 ; i++)
	{
		*ARR=ENC_Read();
		ARR++;
	}
}

uint16 Get_Angle(void)
{
	Arr_Of_Readings(&arr);
	ENC_Read_avg(&arr);
}
