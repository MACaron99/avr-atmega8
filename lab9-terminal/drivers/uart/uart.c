#include <avr/io.h>
#include "uart.h"
#include "../buffer/buffer.h"


#define F_CPU                            16000000UL
#define BAUD                             9600

static buffer_t rx_buffer;
static buffer_t tx_buffer;



int8_t uart_get( uint8_t *byte )
{
	return buffer_get(&rx_buffer, byte);
}

int8_t uart_put( uint8_t byte )
{
	return buffer_put(&tx_buffer, byte);
}

static void uart_transmit( void )
{
	uint8_t byte;

	if( UCSRA & (1 << UDRE) )
	{
		if( buffer_get(&tx_buffer, &byte) )
		{
			UDR = byte;
		}
	}

}

static void uart_receive( void )
{
	if( UCSRA & (1 << RXC) )
	{
//		buffer_put(&tx_buffer, UDR);
		buffer_put(&rx_buffer, UDR);
	}
}

void uart_proc( void )
{
	uart_receive();
	uart_transmit();
}

void uart_init( void )
{
	unsigned int ubrr = F_CPU / 16 / BAUD - 1;

	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;

	UCSRB = (1 << RXEN) | (1 << TXEN);

	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);

	buffer_init(&rx_buffer);
	buffer_init(&tx_buffer);
}
