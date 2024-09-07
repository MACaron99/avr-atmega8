#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"


volatile uint16_t sys_counter;



void sys_timer_init( void )
{
	TCNT0 = 56;
	TIMSK |= (1 << TOIE0);
	TCCR0 = (1 << CS01);
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
