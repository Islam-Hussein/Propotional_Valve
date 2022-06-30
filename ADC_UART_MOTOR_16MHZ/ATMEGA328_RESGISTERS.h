/*
 * ATMEGA328_RESGISTERS.h
 *
 * Created: 5/19/2022 10:26:22 AM
 *  Author: islam
 */ 


#ifndef ATMEGA328_RESGISTERS_H_
#define ATMEGA328_RESGISTERS_H_

#include "STD.h"




/*************************************       DIO_PORTB     ***************************************/

#define DDRB  (*(volatile uint8*)(0x24))
#define PORTB (*(volatile uint8*)(0x25))
#define PINB  (*(volatile uint8*)(0x23))

/*************************************       DIO_PORTC     ***************************************/

#define DDRC  (*(volatile uint8*)(0x27))
#define PORTC (*(volatile uint8*)(0x28))
#define PINC  (*(volatile uint8*)(0x26))

/*************************************       DIO_PORTD     ***************************************/

#define DDRD  (*(volatile uint8*)(0x2A))
#define PORTD (*(volatile uint8*)(0x2B))
#define PIND  (*(volatile uint8*)(0x29))

/*************************************       TIMER 0     ***************************************/


#define OCR0A  (*(volatile uint8*)(0x47))

#define OCR0B  (*(volatile uint8*)(0x48))

#define TCCR0A  (*(volatile uint8*)(0x44))

#define TCCR0B  (*(volatile uint8*)(0x45))

#define TCNT0  (*(volatile uint8*)(0x46))

#define TIMSK1  (*(volatile uint8*)(0x6F))

#define TIMSK2  (*(volatile uint8*)(0x70))


//#define OCR0   (*(volatile uint8*)(0x5C))

/*************************************       TIMER 1     ***************************************/

#define SREG    (*(volatile uint8*)(0x5F))

/*
#define TCCR1A   (*(volatile uint8*)(0x80))

#define TCCR1B   (*(volatile uint8*)(0x81))

#define TCCR1C   (*(volatile uint8*)(0x82))

#define TCNT1L   (*(volatile uint16*)(0x84))

#define TCNT1H   (*(volatile uint16*)(0x85))

#define OCR1AL    (*(volatile uint16*)(0x88))

#define OCR1AH    (*(volatile uint16*)(0x89))

#define OCR1BL    (*(volatile uint16*)(0x8A))

#define OCR1BH    (*(volatile uint16*)(0x8B))

#define ICR1L     (*(volatile uint8*)(0x86))

#define ICR1H     (*(volatile uint8*)(0x87))
*/
/***************************** EXT_INT *********************/
/*
#define SREG    (*(volatile uint8*)(0x5F))
#define MCUCR   (*(volatile uint8*)(0x55))
#define MCUSR  (*(volatile uint8*)(0x54))
#define GICR    (*(volatile uint8*)(0x5B))
#define GIFR    (*(volatile uint8*)(0x5A))

*/
/*************************************        UART         ***************************************/

#define UBRRH  (*(volatile uint8*)(0x40))
#define UBRRL  (*(volatile uint8*)(0x29))
#define UCSRA  (*(volatile uint8*)(0x2B))
#define UCSRB  (*(volatile uint8*)(0x2A))
#define UCSRC  (*(volatile uint8*)(0x40))
#define UDR    (*(volatile uint8*)(0x2C))


/*************************************        SPI        ***************************************/
/*
typedef struct
{
	uint8 SPR0 : 1;
	uint8 SPR1 : 1;
	uint8 SPHA : 1;
	uint8 CPOL : 1;
	uint8 MSTR : 1;
	uint8 DORD : 1;
	uint8 SPE  : 1;
	uint8 SPIE : 1;
	
}SPCR_REG;

typedef struct
{
	SPCR_REG SPCR;
	uint8	 SPSR;
	uint8    SPDR;
	
}SPI_REG;

#define SPI ((volatile SPI_REG*)(0x2D))


*/









#endif /* ATMEGA328_RESGISTERS_H_ */