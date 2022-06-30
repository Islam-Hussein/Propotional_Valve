
/*
 * DC_MOTOR.h
 *
 * Created: 5/29/2022 2:28:51 AM
 *  Author: islam
 */ 

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "DIO.h"
#include "Timer.h"

typedef enum
{
	
	CLOCK_WISE_DIR,
	ANTI_CLOCK_WISE_DIR,
	NO_Direction
	
}DC_MOTOR_DIR;


static DC_MOTOR_DIR Instance_Dir = NO_Direction;

void DCMotor_Init(void);

void DCMotor_SetDir(DC_MOTOR_DIR dir);

void DCMotor_brake(void);

void DCMotor_SetSpeed(uint8 speed);

void DCMotor_Stop(void);

void DCMotor_Drive_Small_Degree(void);

void Set_Speed_Auto(uint16 Desired_Degree);

DC_MOTOR_DIR DC_Motor_Dir_Calc(uint16 Desired_position , uint16 Sitting_Position );







#endif