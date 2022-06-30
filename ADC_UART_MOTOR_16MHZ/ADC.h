
/*
 * ADC.h
 *
 * Created: 6/3/2022 11:07:19 AM
 *  Author: islam
 */ 

#ifndef ADC_H_
#define ADC_H_


#include "STD.h"
#include "STD_MATH.h"
#include <avr/io.h>




void ADC_Init(void);


uint16 Read_ADC(uint8 channel);


#endif