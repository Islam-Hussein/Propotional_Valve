/*
 * DC_MOTOR_TEST_ATMEGA328P.c
 *
 * Created: 5/29/2022 2:28:31 AM
 * Author : islam
 */ 

#define F_CPU 16000000UL


#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>


#include "Driving_with_Cables.h"
#include "UART.h"
#include "ENCODER.h"
#include "DC_MOTOR.h"
#include "ADC.h"
#include "Valve_Functions.h"
#include "Timer.h"



int StringToInteger (char string[]);

extern UART_BUFFER[50];
Calibration_Mode calibration_mode = Calibration_Mode_OFF;
MODE_OF_OPERATION  mode = NO_MODE;
//SITTIING_POSITION Pos = NONE;

uint16 Desired_Degree = 0;
uint8 GLOBAL_SPEED = 0;

//CABLE_DRIVING_MODE Cable_Driving_Mode = NONE;

int ziel = 0;

/**************************** ANGLES INITIALIZATION ****************************************/
int  max_right_angle = 0;
int  max_left_angle = 0;
int  Middle_Position = 0;

uint16 const RIGHT_ADDR  =  0x10;   //Address of RIGHT Position in EEPROM
uint16 const  LEFT_ADDR   =  0x20;	//Address of LEFT Position in EEPROM
uint16 const  MIDDLE_ADDR =  0x00;	//Address of MIDLLE Position in EEPROM

int  Reached_Position = 0;

static bool Drive_Pink = false;
static bool Drive_Blue = false;
//uint16 ziel  = 230 ;

extern cables;
extern POSITION;
extern circle;

bool EINGELERNET;


int main(void)
{
	
	DCMotor_Init();
	ENC_Init();
	UART_Init();
	ADC_Init();
	Dip_Switch_Init();
	Update_Boundries();
	//Winkel_Timer_Init();
	//Timer1_Init();
	
	//Timer1_SetDelay(30);
	
	//Timer1_Start();
	
	if(Middle_Position == 0xFF)
	{
		EINGELERNET = false;
	}
	
    /* Replace with your application code */
    while (1) 
    {

		
		Update_Mode();
		if(mode == CALIBRATION_MODE)
		{
			Calibration();
		}
		if(mode == DRIVING_MODE)
		{
			
			//Update_Global_ADC_Direction();
			//ADC_DRIVE_TEST();	
			//Drive_Untill_Reach_End();		
			//Drive_Untill_Reach_End();
			CABLES_READ();
			FAHREN();
			//Generic_Drive();
			
			if((Read_ADC(PINK_CABLE) < 400) && (Read_ADC(BLUE_CABLE) < 400))
			{
				if(POSITION != MIDDLE)
				{
					uint16 ziel = Middle_Position;

					DCMotor_SetDir(DC_Motor_Dir_Calc(ziel , ENC_Read_In_Degree())); //Calculate the shortest route to Desired Position
					DCMotor_SetSpeed(10);
					while(!(abs(ziel - ENC_Read_In_Degree()  < 3))) // The programm will be stuck here until DC Motor get close to the Desired position
					{
						UART_SendString(itoa(ENC_Read_In_Degree() , UART_BUFFER , 10));
						UART_SendByte('\n');
					}
					DCMotor_Stop();
					POSITION = MIDDLE;
				}
			} 
		}	
		UART_SendString(itoa(ENC_Read_In_Degree() , UART_BUFFER , 10));
		UART_SendByte('\n');		
		
	}
		

			

}









ISR (TIMER1_COMPA_vect)
{
	static uint8 cnt = 0;
	
	cnt++;
	
	if(cnt == 1)
	{
		cnt = 0;
		
		UART_SendString(itoa(ENC_Read_In_Degree() , UART_BUFFER , 10));
		UART_SendByte('\n');
		
		//UART_Send_Degree(ENC_Read_In_Degree());
		
		//UART_SendByte(ENC_Read_In_Degree());
	}
	
}


