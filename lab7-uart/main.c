
#include <system.h>
#include <avr/interrupt.h>

#include "drivers/button/button.h"
#include "drivers/led/led.h"
#include "drivers/matrix/matrix.h"
#include "drivers/multiplexer/multiplexer.h"
#include "drivers/uart/uart.h"



#define F_CPU                            16000000UL
#define BAUD                             9600
#define MYUBRR                           F_CPU/16/BAUD-1



volatile uint16_t sys_counter;



void sys_timer_init( void )
{
	TCNT0   = 56;
	TIMSK  |= (1 << TOIE0);
	TCCR0   = (1 << CS01);
}


ISR( TIMER0_OVF_vect )
{
	TCNT0 = 56;

	sys_counter++;
}


uint16_t sys_timer_get( void )
{
	uint16_t counter;

	cli();
	counter = sys_counter;
	sei();

	return counter;
}


void io_init( void )
{
	DDRB |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
	DDRC |= (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
	DDRD |= (1 << 2) | (1 << 3) | (1 << 6) | (1 << 7);

	PORTC |= (1 << 5);
}


void main( void ) __attribute__ ((noreturn));
void main( void )
{
	sys_wdt_enable();
	io_init();
	sys_timer_init();
	uart_init(MYUBRR);
	sys_int_enable();

	for( ;; )
	{
		sys_wdt_reset();

		button_proc( sys_timer_get() );
		led_proc( sys_timer_get() );
		led_snake_proc( sys_timer_get() );
		multi_proc();
		matrix_loop();

		uart_transmit( sys_timer_get(), 'F' );
	}
}
