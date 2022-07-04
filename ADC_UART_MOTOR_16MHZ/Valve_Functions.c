
/*
 * Valve_Functions.c
 *
 * Created: 6/3/2022 12:31:20 PM
 *  Author: islam
 */ 

#include "Valve_Functions.h"


uint16 const THRESHOLD =  400;
DC_MOTOR_DIR LAST_DIR = NO_Direction;
DC_MOTOR_DIR MOTOR_DIR_WITH_ADC = NO_Direction;
MODE_OF_OPERATION OPERATION;



extern Cable_Driving_Mode;
extern UART_BUFFER;


Position_Flag POSITION;

extern  Reached_Position;


extern calibration_mode;
extern mode;
extern Pos;



extern  max_left_angle;
extern  max_right_angle;
extern  Middle_Position;

extern LEFT_ADDR;
extern RIGHT_ADDR;
extern MIDDLE_ADDR;

extern circle;

extern Drive_Pink ;
extern Drive_Blue ;

extern EINGELERNET;

struct CABLES
{
	bool PINK_READ;
	bool BLUE_READ;
};

DC_MOTOR_DIR DRIVE_WITH_CABLES;

struct CABLES cables;

void CABLES_READ(void)
{
	if(Read_ADC(PINK_CABLE) > THRESHOLD)
	{
		cables.PINK_READ =true;
	}
	if(Read_ADC(BLUE_CABLE) > THRESHOLD)
	{
		cables.BLUE_READ =true;
	}
	if(Read_ADC(PINK_CABLE) < THRESHOLD)
	{
		cables.PINK_READ = false;
	}
	if(Read_ADC(BLUE_CABLE)  < THRESHOLD)
	{
		cables.BLUE_READ =false;
	}
	if((Read_ADC(PINK_CABLE) > THRESHOLD) && (Read_ADC(BLUE_CABLE) > THRESHOLD))
	{
		cables.BLUE_READ =false;
		cables.PINK_READ =false;

	}
}

void ADC_DRIVE_TEST(void)
{
	if(MOTOR_DIR_WITH_ADC == CLOCK_WISE_DIR)
	{
		DCMotor_SetDir(MOTOR_DIR_WITH_ADC);
		DCMotor_SetSpeed(10);
		LAST_DIR = 	CLOCK_WISE_DIR;	
	}
	else if(MOTOR_DIR_WITH_ADC == ANTI_CLOCK_WISE_DIR)
	{
		DCMotor_SetDir(MOTOR_DIR_WITH_ADC);
		DCMotor_SetSpeed(10);
		LAST_DIR = ANTI_CLOCK_WISE_DIR;		
	}
	else if ((MOTOR_DIR_WITH_ADC == CLOCK_WISE_DIR) || (MOTOR_DIR_WITH_ADC == ANTI_CLOCK_WISE_DIR) || (LAST_DIR != NO_Direction))
	{
		DCMotor_Stop();
		LAST_DIR = NO_Direction;
	}
	else if(LAST_DIR == NO_Direction)
	{
		DIO_SetPortValue(DIO_PORTD , DIO_PORT_LOW);		
	}
}


void Calibration_Mode_Check(void)
{
	uint16 DIP_Switch_1 = Read_ADC(PINC5);
	uint16 DIP_Switch_2 = Read_ADC(PINC4);
 
	
	if((DIP_Switch_1 > THRESHOLD) && (DIP_Switch_2 < THRESHOLD))
	{
		calibration_mode = Calibration_Mode_ON;
	}
	else
	{
		calibration_mode = Calibration_Mode_OFF;
	}

}

void Dip_Switch_Init(void)
{
	DIO_SetPinDir(DIO_PORTC , DIO_PIN4 , DIO_PIN_INPUT);
	DIO_SetPinDir(DIO_PORTC , DIO_PIN5 , DIO_PIN_INPUT);
}





void Update_Global_ADC_Direction(void)
{
	if((Read_ADC(PINK_CABLE) > THRESHOLD) && (Read_ADC(BLUE_CABLE) < THRESHOLD))
	{
		//MOTOR_DIR_WITH_ADC = CLOCK_WISE_DIR;
		//CABLE_DRIVING_MODE = RIGHT;
		if(	Reached_Position != max_right_angle)
		{
			Cable_Driving_Mode = RIGHT;	
			POSITION = RIGHT;
			
		}		
		
		
		
	}
	else if((Read_ADC(BLUE_CABLE) > THRESHOLD) && (Read_ADC(PINK_CABLE) < THRESHOLD))
	{
		if(	Reached_Position != max_left_angle)
		{
			Cable_Driving_Mode = LEFT;
			POSITION = LEFT;

		}
		//MOTOR_DIR_WITH_ADC = ANTI_CLOCK_WISE_DIR;
		//CABLE_DRIVING_MODE = LEFT;


	}
	
	else if ((Read_ADC(BLUE_CABLE) < THRESHOLD) && (Read_ADC(PINK_CABLE) < THRESHOLD) )
	{
		if(	Reached_Position != Middle_Position)
		{
			Cable_Driving_Mode = MIDDLE;			
		}
		//CABLE_DRIVING_MODE = MIDDLE;



		//MOTOR_DIR_WITH_ADC = DC_Motor_Dir_Calc(Middle_Position , ENC_Read_In_Degree());
		//MOTOR_DIR_WITH_ADC = NO_Direction;
		//DCMotor_Stop();
	}
	 
	
	else
	{
		
		//Cable_Driving_Mode = NONE;

		//MOTOR_DIR_WITH_ADC = NO_Direction;
		//DCMotor_Stop();
	}
	

}


void Update_Mode(void)
{
	uint16 DIP_Switch_1 = Read_ADC(PINC5);
	uint16 DIP_Switch_2 = Read_ADC(PINC4);	
	
	if((DIP_Switch_1 > THRESHOLD) && (DIP_Switch_2 < THRESHOLD))
	{
		mode = CALIBRATION_MODE;
	}
	if ((DIP_Switch_2 > THRESHOLD) && (DIP_Switch_1 < THRESHOLD))
	{
		mode = DRIVING_MODE;
	}
	if(((DIP_Switch_2 < THRESHOLD) && (DIP_Switch_1 < THRESHOLD)) || (((DIP_Switch_2 > THRESHOLD) && (DIP_Switch_1 > THRESHOLD))) )
	//if((DIP_Switch_2 < THRESHOLD) && (DIP_Switch_1 < THRESHOLD)) 
	{
		//mode = Idle_Mode;
		mode =  NO_MODE;
	}
}


/*
void Drive_Untill_Reach_End(void)
{
	if(Cable_Driving_Mode == RIGHT)
	{
		Drive_To_Max_Right();
	}
	else if(Cable_Driving_Mode == LEFT)
	{
		Drive_To_Max_Left();
	}
	else if(Cable_Driving_Mode == MIDDLE)
	{
		Drive_To_Middle_Position();
	}
	
	else
	{
		DIO_SetPortValue(DIO_PORTD , DIO_PORT_LOW);
		//DCMotor_Stop();
	}	
	
}
*/

/*
void Drive_Untill_Reach_End(void)
{
	if(MOTOR_DIR_WITH_ADC = CLOCK_WISE_DIR && Reached_Position != max_right_angle )
	{
		Drive_To_Max_Right();
	}
	else if(MOTOR_DIR_WITH_ADC = ANTI_CLOCK_WISE_DIR && Reached_Position != max_left_angle )
	{
		Drive_To_Max_Left();
	}
	else if(MOTOR_DIR_WITH_ADC == NO_Direction && Reached_Position != Middle_Position )
	{
		Drive_To_Middle_Position();
	}
	
	else
	{
		DIO_SetPortValue(DIO_PORTD , DIO_PORT_LOW);
		//DCMotor_Stop();
	}
	
}
*/
/*
void FAHREN(void)
{
	if(cables.BLUE_READ  && (POSITION != LEFT))
	{
		//Drive_To_Max_Left();
		Drive_Untill_Reach_Degree(max_left_angle);
		POSITION = LEFT;
		Reached_Position = max_left_angle;

		//DRIVE_WITH_CABLES =  CLOCK_WISE_DIR;
	}
	if(cables.PINK_READ  && (POSITION != RIGHT))
	{
		Drive_Untill_Reach_Degree(max_right_angle);
		POSITION != RIGHT;
		Reached_Position = max_right_angle;

		//Drive_To_Max_Right();
		//DRIVE_WITH_CABLES =  ANTI_CLOCK_WISE_DIR;

	}
	
	
}

*/


void FAHREN(void)
{
	if(cables.BLUE_READ)
	{
		Drive_To_Max_Left();
		//DRIVE_WITH_CABLES =  CLOCK_WISE_DIR;
	}
	if(cables.PINK_READ)
	{
		Drive_To_Max_Right();
		//DRIVE_WITH_CABLES =  ANTI_CLOCK_WISE_DIR;

	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Generic_Drive(void)
{
	DCMotor_SetDir(DRIVE_WITH_CABLES);
	int End = 0;
	if(DRIVE_WITH_CABLES == CLOCK_WISE_DIR)
	{
		End = max_left_angle;
	}
	if(DRIVE_WITH_CABLES == ANTI_CLOCK_WISE_DIR)
	{
		End = max_right_angle;
				
	}
	if(DRIVE_WITH_CABLES == NO_Direction)
	{
		End = Middle_Position;		
	}
	DCMotor_SetSpeed(10);
	while(!(abs(End - ENC_Read_In_Degree()  < 3))); // The programm will be stuck here until DC Motor get close to the Desired position
	DCMotor_Stop();
	
}



void Drive_To_Max_Right(void)
{
	if(POSITION != RIGHT)
	{
		
	
		uint16 End_Position = max_right_angle;
		DCMotor_SetDir(DC_Motor_Dir_Calc(End_Position , ENC_Read_In_Degree())); //Calculate the shortest route to Desired Position
		DCMotor_SetSpeed(10);
		while(!(abs(End_Position - ENC_Read_In_Degree()  < 3))) // The programm will be stuck here until DC Motor get close to the Desired position
		{
			UART_SendString(itoa(ENC_Read_In_Degree() , UART_BUFFER , 10));
			UART_SendByte('\n');
					
		}
		DCMotor_Stop();
		POSITION =RIGHT;
	
		Reached_Position = max_right_angle;	
	}
}

void Drive_To_Max_Left(void)
{
	if(POSITION != LEFT)
	{
		
	
		uint16 End_Position = max_left_angle;
		DCMotor_SetDir(DC_Motor_Dir_Calc(End_Position , ENC_Read_In_Degree())); //Calculate the shortest route to Desired Position
		DCMotor_SetSpeed(10);
		while(!(abs(End_Position - ENC_Read_In_Degree())  < 2)) // The programm will be stuck here until DC Motor get close to the Desired position
		{
			UART_SendString(itoa(ENC_Read_In_Degree() , UART_BUFFER , 10));
			UART_SendByte('\n');
					
		}
		DCMotor_Stop();	
		Reached_Position = max_left_angle;
		POSITION = LEFT;
	}
}

void Drive_To_Middle_Position(void)
{
	/*
	uint16 End_Position = Middle_Position;
	DCMotor_SetDir(DC_Motor_Dir_Calc(Middle_Position , ENC_Read_In_Degree())); //Calculate the shortest route to Desired Position
	DCMotor_SetSpeed(10);
	while(!(abs(Middle_Position - ENC_Read_In_Degree() ) < 2)); // The programm will be stuck here until DC Motor get close to the Desired position
	DCMotor_Stop();
	*/
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



void Drive_Untill_Reach_Degree(uint16 Desired_Degree)
{
	DCMotor_SetDir(DC_Motor_Dir_Calc(Desired_Degree , ENC_Read_In_Degree())); //Calculate the shortest route to Desired Position
	DCMotor_SetSpeed(10);
	while(!(abs(Desired_Degree - ENC_Read_In_Degree() ) < 3)); // The programm will be stuck here until DC Motor get close to the Desired position
	DCMotor_Stop();	
}


void Update_Boundries(void)
{
	max_right_angle = eeprom_read_word (  (uint16 *) RIGHT_ADDR );
	max_left_angle  = eeprom_read_word (  (uint16 *) LEFT_ADDR );
	Middle_Position = eeprom_read_word (  (uint16 *) MIDDLE_ADDR );
	
}



void Calibration(void)
{
	DCMotor_SetDir(CLOCK_WISE_DIR);
	DCMotor_SetSpeed(10);
	
	_delay_ms(800);
	
	DCMotor_Stop();
	_delay_ms(500);
	
	max_right_angle = ENC_Read_In_Degree();
	
	
	DCMotor_SetDir(ANTI_CLOCK_WISE_DIR);
	DCMotor_SetSpeed(10);
	
	_delay_ms(800);
	
	DCMotor_Stop();
	_delay_ms(500);

	
	max_left_angle = ENC_Read_In_Degree();
	
	if(max_right_angle > max_left_angle)
	{

		Middle_Position = max_left_angle + ((max_right_angle - max_left_angle) / 2 );

	}
	else
	{
		Middle_Position = (max_left_angle + max_right_angle) / 2;
		if(Middle_Position > (circle / 2))
		{
			
			Middle_Position -= (circle /2);
		}
	}
	
	eeprom_update_word((uint16 *) LEFT_ADDR , max_left_angle);
	eeprom_update_word((uint16 *) RIGHT_ADDR , max_right_angle);
	eeprom_update_word((uint16 *) MIDDLE_ADDR , Middle_Position);
	
	EINGELERNET = true;
	
	
}
