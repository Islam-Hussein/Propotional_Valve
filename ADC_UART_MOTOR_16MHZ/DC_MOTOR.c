
/*
 * DC_MOTOR.c
 *
 * Created: 5/29/2022 2:29:03 AM
 *  Author: islam
 */ 

#include "DC_MOTOR.h"
#include "ENC_Cfg.h"
#include <util/delay.h>

#define Circle_in_Bits  2^ENC_MODE 

uint16 const circle = 360;

extern Desired_Degree;
extern GLOBAL_SPEED;



void DCMotor_Init(void)
{
	DIO_SetPinDir(DIO_PORTD , DIO_PIN5 , DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTD , DIO_PIN6 , DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTD , DIO_PIN7 , DIO_PIN_OUTPUT);
}

void DCMotor_SetDir(DC_MOTOR_DIR dir)
{
	switch (dir)
	{
		case CLOCK_WISE_DIR :
		DIO_SetPinDir(DIO_PORTD, DIO_PIN5, DIO_PIN_INPUT);
		DIO_SetPinDir(DIO_PORTD, DIO_PIN6, DIO_PIN_OUTPUT);
		DIO_SetPinValue(DIO_PORTD, DIO_PIN7, DIO_PIN_HIGH);

		Instance_Dir = CLOCK_WISE_DIR;
		
		break;
		
		case ANTI_CLOCK_WISE_DIR :
		DIO_SetPinDir(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);
		DIO_SetPinDir(DIO_PORTD, DIO_PIN6, DIO_PIN_INPUT);
		DIO_SetPinValue(DIO_PORTD, DIO_PIN7, DIO_PIN_HIGH);
		
		Instance_Dir = ANTI_CLOCK_WISE_DIR;

		break;
		
		case NO_Direction:
		DIO_SetPortValue(DIO_PORTD , DIO_PORT_LOW);
		break;
		
		
		default :
		break;
	}	
}



void DCMotor_SetSpeed(uint8 speed)
{
	GLOBAL_SPEED = speed;
	
	speed *= 10;
	
	
	
	
	switch (Instance_Dir)
	{
		case CLOCK_WISE_DIR :
		/*
		TCCR0A|= (1<<WGM00)|(1<<COM0A1)  ;
		//TCCR0B|= (1<<CS01);		//Vorteiler = 8
		TCCR0B |= (1<<CS02) |(1 << CS01) | (1 << CS00) ;
		OCR0A = ((speed * 256 )/100) - 1;
		*/
		DIO_SetPinValue(DIO_PORTD, DIO_PIN6, DIO_PIN_HIGH);
		
		break;
		
		case ANTI_CLOCK_WISE_DIR :
		/*
		TCCR0A|= (1<<WGM00)|(1<<COM0B1)  ;
		//TCCR0B|= (1<<CS01);		//Vorteiler = 8
		TCCR0B |= (1<<CS02) | (1 << CS01) | (1 << CS00) ;
		OCR0B = ((speed * 256 )/100) - 1;
		*/
		DIO_SetPinValue(DIO_PORTD, DIO_PIN5, DIO_PIN_HIGH);
		
		break;
		
		
		default :
		break;
	}
	
}

void DCMotor_Drive_Small_Degree(void)
{

	DC_Motor_Dir_Calc(Desired_Degree , ENC_Read_In_Degree());
	DCMotor_SetSpeed(10);
	_delay_ms(50);
	DCMotor_Stop();
	_delay_ms(50);
}




void Set_Speed_Auto(uint16 Desired_Degree)
{
	uint16 Current_Position = ENC_Read_In_Degree();
	uint8 speed = 0;
	
	if(abs(Current_Position - Desired_Degree) > 10)
	{
		speed = 10;
	}
	
	if((abs(Current_Position - Desired_Degree)) < 10)
	{
		speed = 3;
	}
	
	DCMotor_SetSpeed(speed);
}




void DCMotor_brake(void)
{

	for(uint8 i = GLOBAL_SPEED ; i > 0 ; i++ )
	{
		DCMotor_SetSpeed(i);
		_delay_ms(20);
	}
}



void DCMotor_Stop(void)
{

	
	DIO_SetPortValue(DIO_PORTD , DIO_PORT_HIGH);
	_delay_ms(500);
	DIO_SetPortValue(DIO_PORTD , DIO_PORT_LOW);
	
	Instance_Dir = NO_Direction;	
	GLOBAL_SPEED = 0;
}

DC_MOTOR_DIR DC_Motor_Dir_Calc(uint16 Desired_position , uint16 Sitting_Position )
{
	int Route = 0;
	
	if (Desired_position > Sitting_Position)
	{
		Route = Desired_position - Sitting_Position;

		if (Route > circle/2)
		{
			return ANTI_CLOCK_WISE_DIR;
		}
		else if (Route < circle/2)
		{
			return CLOCK_WISE_DIR;
		}
		else if (Route == circle/2)
		{
			return ANTI_CLOCK_WISE_DIR;
		}
	}
	
	if (Desired_position < Sitting_Position)
	{
		Route = Sitting_Position - Desired_position;
		
		if (Route > circle/2)
		{
			return CLOCK_WISE_DIR;
		}
		else if (Route < circle/2)
		{
			return ANTI_CLOCK_WISE_DIR;
		}
		else if (Route == circle/2)
		{
			return CLOCK_WISE_DIR;
		}
	}	
}

