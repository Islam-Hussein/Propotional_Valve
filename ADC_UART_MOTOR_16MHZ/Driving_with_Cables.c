
/*
 * Driving_with_Cables.c
 *
 * Created: 6/10/2022 10:25:43 AM
 *  Author: islam
 */ 
#include "Driving_with_Cables.h"
#define THRESHOLD 500


typedef enum 
{
	RIGHT,
	LEFT,
	IDLE
	}Drive_Flag;
	
typedef enum
{
	IS_MOVING,
	IS_STOP
}MOTOR_STATE;
	
MOTOR_STATE Motor_State;
 	
	
Drive_Flag Dir;

void Drive(void)
{
	if(Dir == RIGHT)
	{
		DCMotor_SetDir(CLOCK_WISE_DIR);
		DCMotor_SetSpeed(10);
		Motor_State = IS_MOVING;
	} 
	if(Dir == LEFT)
	{
		DCMotor_SetDir(ANTI_CLOCK_WISE_DIR);
		DCMotor_SetSpeed(10);
		Motor_State = IS_MOVING;
	}
	if(Dir == IDLE)
	{
		if(Motor_State == IS_MOVING)
		{
			DCMotor_Stop();
			Motor_State = IS_STOP;
		}
		if(Motor_State == IS_STOP)
		{
			DIO_SetPortValue(DIO_PORTD , DIO_PORT_LOW);
		}

	}
}

void Update_Drive_Flag(void)
{
	if((Read_ADC(PINK_CABLE) > THRESHOLD) && (Read_ADC(BLUE_CABLE) < THRESHOLD))
	{
		Dir = RIGHT;
	}
	if((Read_ADC(PINK_CABLE) > THRESHOLD) && (Read_ADC(BLUE_CABLE) < THRESHOLD))
	{
		Dir = LEFT;
	}
	if(((Read_ADC(PINK_CABLE) < THRESHOLD) && (Read_ADC(BLUE_CABLE) < THRESHOLD)) || ((Read_ADC(PINK_CABLE) > THRESHOLD) && (Read_ADC(BLUE_CABLE) > THRESHOLD)))
	{
		Dir = IDLE;
	}
}