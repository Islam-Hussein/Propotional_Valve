/*
 * Timer.c
 *
 * Created: 16.03.2022 10:41:35
 *  Author: student
 */ 

#include "Timer.h"

uint8    Init_Value = 0;
uint32   Number_OVRflows  = 0; 

/*
void Timer0_Init(void)
{
	TCCR0A |= 0x00;
	
	//TIMSK |= 0x01;
	
	//SREG  |= 0x80;
}

void Timer0_Start(void)
{
	TCCR0B |= 0x02;
}

void Timer0_Stop(void)
{
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
}

void Timer0_SetDelay(uint32 Delay_Ms)
{
	
	uint8 Tick_Time = (1024 / 16) ;
	
	uint32 Total_Ticks = (Delay_Ms * 1000) / Tick_Time ;
	
	Number_OVRflows = Total_Ticks / 256;
	
	Init_Value   = 256 - (Total_Ticks % 256);
	
	TCNT0 = Init_Value ;
	
	Number_OVRflows++;  
}

*/

void Timer1_Init(void)
{	
	TCCR1B |= 0x08;
	TIMSK1 |= 0x02;
	SREG   |= 0x80;
}

void Timer1_Start(void)
{
	TCCR1B |= 0x05;
}

void Timer1_Stop(void)
{
		CLR_BIT(TCCR1B,0);
		CLR_BIT(TCCR1B,1);
		CLR_BIT(TCCR1B,2);
}

void Timer1_SetDelay(uint32 Delay_Ms)
{
	if (Delay_Ms <= 4000)
	{
		uint8 Tick_Time = 1024 /16 ;
		
		uint32 Num_Ticks = (Delay_Ms * 1000) / Tick_Time ;
		
		OCR1A = Num_Ticks -1 ;
	}
	
}


/*
void PWM0_Init(DC_MOTOR_DIR Dir)
{

	
	TCCR0A |= 0x01; //--> WGM00 IS ENABLED --> Phase Corrected Mode
	//TCCR0B |= 0x02; //--> Vorteiler 8 --> Only CS01 is ENABLED

	if (Dir == CLOCK_WISE_DIR)
	{
		TCCR0A |= 0x80; //--> COM0A1 is ENABLED CLEAR ON COMPARE MATCH
	}
	if (Dir == ANTI_CLOCK_WISE_DIR)
	{
		TCCR0A |= 0x20; //--> COM0B1 is ENABLED
	}
	
	
	//TCCR0 |= 0x68;  
}

void PWM0_Generate(uint16 Duty_Cycle , DC_MOTOR_DIR Dir)
{
	if (Dir == CLOCK_WISE_DIR)
	{
		OCR0A = ((Duty_Cycle * 256 )/100) - 1;
	}
	if(Dir == ANTI_CLOCK_WISE_DIR)
	{
		OCR0B = ((Duty_Cycle * 256 )/100) - 1;		
	}

}



void PWM0_Start(void)
{

	TCCR0B |= 0x02;  //--> CS01 is ENABLED --> 8 Prescaler --> MOTOR Will ONLY Start when clock is provided
	
	
	//TCCR0 |= 0x03;
	
}


/*
void PWM1_Init(void)
{
	DDRD |= 0x20;
	
	TCCR1A |= 0x02;
	TCCR1B |= 0x18;
	
	ICR1 =1250;  //625
}

void PWM1_Generate(uint16 duty_cycle)
{
	OCR1A = ((duty_cycle * 1250 ) / 100) - 1 ;
}


void PWM1_Start(void)
{
	TCCR1B |= 0x04;
}
*/