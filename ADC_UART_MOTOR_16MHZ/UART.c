/*
 * UART.c
 *
 * Created: 11.02.2022 09:26:59
 *  Author: student
 */ 

#include "UART.h"



volatile char UART_BUFFER[50] = {'f'};
volatile uint8 flag = 0;






void UART_Init(void)
{
	
	uint32 BR_Value = 0;
	
	DIO_SetPinDir(PORTD, PIND0, DIO_PIN_INPUT);
	DIO_SetPinDir(PORTD, PIND1, DIO_PIN_OUTPUT);
	


	UCSR0B |= 0x18 ; // --> RXEN0 - TXEN0 --> Enabled Transmit and Receive
	//UCSR0B |= 0xC0 ; // --> RXCIE0 - TXCIE0 --> to enable uart RX and TX Interrupt if you don't want Interrupt and keep polling just Comment the line 
	UCSR0C |= 0x06 ; // --> Only  UCSZ00 and UCSZ01 are set --> 8-Bit Frame
	
	/* When setting Baud Rate with 1MHz you must set it to 2400 because the internal OSC is not reliable and if you changed it to 9600 it will send false readings */
	
	#if F_CPU == 1000000UL
	
	BR_Value = ((10000) / (16 * (2400))) - 1;

	#endif
	
	#if F_CPU == 16000000UL
	
	BR_Value = ((160000) / (16 * (96))) - 1;

	#endif
	
	#if F_CPU == 8000000UL
		
	BR_Value = ((80000) / (16 * (96))) - 1;

	#endif
	
	
	//BR_Value = ((160000) / (16 * (192))) - 1;
	
	UBRR0H = (BR_Value) >> 8;
	UBRR0L = (BR_Value & 0xFF);
	
}

void UART_SendByte(uint8 data)
{
	/*
	UDR0 = data;
	
	while(GET_BIT(UCSR0A , 5) == 0 );
	*/
	while(!(UCSR0A & (1 << UDRE0 )));
	
	UDR0 = data;
	
}

void UART_SendString(uint8* str)
{
	uint8 i = 0;
	
	while(UART_BUFFER[i] != '\0')
	{
		UART_SendByte(UART_BUFFER[i]);
		i++;
	}
		
}

uint8 UART_ReceiveByte(void)
{
	/*
	uint8 data = 0;
	
	while(GET_BIT(UCSR0A , 7) == 0);
	
	data = UDR0;
	
	return data;
	*/
	uint8 data;
	
	while(!(UCSR0A & (1 << RXC0)));
	
	data = UDR0;
	
	return data;
	
	
}

uint8* UART_ReceiveString(void)
{
	//static uint8 UART_BUFFER[50] = {'n'};
		int i = 0 ;
		
		while (UART_BUFFER[i] != '\0')
		{
			UART_BUFFER[i] = UART_ReceiveByte();
			i++;
		} 
	return UART_BUFFER;
	  
}

uint16 UART_ReceiveDegree(void)
{
	uint16 data = 0;
	uint8 tmp = 0;
	
	data = UART_ReceiveByte();
	tmp  = UART_ReceiveByte();
	if(tmp)
	{
		data  = (data << 8);
		data |= tmp;
	}
	return data;
}

void UART_Send_Degree(uint16 Degree)
{
	uint8 tmp = (Degree>>8);
	UART_SendByte(tmp);
	UART_SendByte(Degree);
}



/*
ISR(USART_RX_vect)
{
	static uint8 i = 0;
	
	UART_BUFFER[i] = UDR0;
	
	if(UART_BUFFER[i] == '\0' )
	{
		i = 0;
	}
	
	i++;
}
*/
/*
ISR(USART_TX_vect)
{
	uint8 str_index = 0;
	
	while(str[str_index] != '\0')
	{
		str[str_index] = UDR0;
			
		str_index++;
	}
	
}
*/