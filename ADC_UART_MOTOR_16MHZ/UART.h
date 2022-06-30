/*
 * UART.h
 *
 * Created: 11.02.2022 09:27:18
 *  Author: student
 */ 


#ifndef UART_H_
#define UART_H_

#include "DIO.h"
#include <avr/io.h>

#define F_CPU 16000000UL


void UART_Init(void);

void UART_SendByte(uint8);

void UART_SendString(uint8* str);

uint8 UART_ReceiveByte(void);

uint8* UART_ReceiveString(void);

uint16 Receive_Degree(void);

void UART_Send_Degree(uint16 Degree);

uint16 UART_ReceiveDegree(void);

#endif /* UART_H_ */