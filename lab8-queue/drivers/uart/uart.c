#include <avr/io.h>
#include "uart.h"
#include "queue.h"

#define F_CPU                            16000000UL
#define BAUD                             9600


static Queue tx_queue;



int8_t uart_put( uint8_t byte )
{
	return queue_enqueue(&tx_queue, byte);
}


//int8_t uart_get( uint8_t *byte )
//{
//
//}


static void uart_set_speed( unsigned int baud_rate )
{
	uint16_t rates[3] = { 9600, 19200, 38400 };
	uint16_t selected_rate = 0;

	for (uint8_t i = 0; i < 3; i++)
	{
		if( baud_rate == rates[i] )
		{
			selected_rate = baud_rate;
			break;
		}
	}

	if( selected_rate == 0 )
	{
		selected_rate = BAUD;
	}

	unsigned int ubrr = F_CPU / 16 / selected_rate - 1;

	UBRRH = ( unsigned char ) (ubrr >> 8);
	UBRRL = ( unsigned char ) ubrr;
}


static void uart_transmit( void )
{
	uint8_t byte;

	if (queue_dequeue(&tx_queue, &byte))
	{
		if (UCSRA & (1 << UDRE))
		{
			UDR = byte;
		}
	}
}


static void uart_receive( void )
{
	if( UCSRA & (1 << RXC) )
	{
		queue_enqueue(&tx_queue, UDR);
	}
}


void uart_proc( void )
{
	uart_transmit();
	uart_receive();
}


void uart_init( void )
{
	uart_set_speed( BAUD );

	UCSRB = (1 << RXEN) | (1 << TXEN);

	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}
