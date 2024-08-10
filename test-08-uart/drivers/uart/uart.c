#include <avr/io.h>
#include "uart.h"



void uart_init( unsigned int ubrr )
{
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;

	UCSRB = (1 << RXEN) | (1 << TXEN);

	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}


void uart_transmit( uint16_t sys_timer, unsigned char data )
{
	static uint16_t timer;

	if (sys_timer - timer < 10000)
		return;
	timer = sys_timer;

	while( !( UCSRA & (1 << UDRE) ) );
	UDR = data;
}

unsigned char uart_receive( void )
{
	while( ( !(UCSRA) ) & (1 << RXC) );
	return UDR;
}
