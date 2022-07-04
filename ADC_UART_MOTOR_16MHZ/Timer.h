
/*
 * Timer.h
 *
 * Created: 16.03.2022 10:41:03
 *  Author: student
 */ 

#ifndef  TIMER_H_
#define  TIMER_H_

#include "ATMEGA328_RESGISTERS.h"
#include "BIT_MATH.h"
#include "DC_MOTOR.h"
#include <avr/interrupt.h>



/*
void Timer0_Init(void);

void Timer0_Start(void);

void Timer0_Stop(void);

void Timer0_SetDelay(uint32 Delay_Ms);



void PWM0_Init(DC_MOTOR_DIR);

void PWM0_Generate0(uint16 Duty_Cycle);

void PWM0_Start(void);

*/



void Timer1_Init(void);

void Timer1_Start(void);

void Timer1_Stop(void);

void Timer1_SetDelay(uint32 Delay_Ms);

/*
void PWM1_Init(void);

void PWM1_Generate(uint16 duty_cycle);

void PWM1_Start(void);

*/




#endif