
/*
 * Valve_Functions.h
 *
 * Created: 6/3/2022 12:19:15 PM
 *  Author: islam
 */ 

#ifndef VALVE_FUNCTIONS_H_
#define VALVE_FUNCTIONS_H_

#define F_CPU 16000000UL


#include "Valve_EXT_Peripherals.h"
#include "ADC.h"
#include "ENCODER.h"
#include "UART.h"
#include "DC_MOTOR.h"
#include "stdbool.h"
#include "STD.h"
#include <avr/io.h>
#include <util/delay.h>



typedef enum 
{
	RIGHT,LEFT,MIDDLE
}Position_Flag;


typedef enum 
{
	Calibration_Mode_OFF,
	Calibration_Mode_ON
	
	}Calibration_Mode;


typedef enum 
{
	CALIBRATION_MODE,
	DRIVING_MODE,
	NO_MODE
	}MODE_OF_OPERATION;

/*
typedef enum
{
	LEFT,
	RIGHT,
	MIDDLE,
	NONE
	
	}SITTIING_POSITION;
	*/
	
	
typedef enum
{
	IS_INIT,
	NOT_INIT
	}INIT_STATUS;

void ADC_DRIVE_TEST(void);

void Calibration_Mode_Check(void);

void Drive_Untill_Reach_Degree(uint16 Desired_Degree);

void Dip_Switch_Init(void);

void Update_Global_ADC_Direction(void);

void Update_Mode(void);

void Drive_Untill_Reach_End(void);

void Drive_To_Max_Right(void);

void Drive_To_Max_Left(void);

void Drive_To_Middle_Position(void);

void CABLES_READ(void);

void FAHREN(void);

void Generic_Drive(void);

void Calibration (void);

void Update_Boundries(void);

#endif