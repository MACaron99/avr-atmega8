
#include <system.h>
#include <avr/interrupt.h>

#include "drivers/button/button.h"
#include "drivers/led/led.h"
#include "drivers/matrix/matrix.h"



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

	PORTC |= (1 << 5);
}


void main( void ) __attribute__ ((noreturn));
void main( void )
{
	sys_wdt_enable();
	io_init();
	sys_timer_init();
	sys_int_enable();

	matrix_led_set(7, 1);
	matrix_led_set(2, 1);
	matrix_led_set(0, 1);
	matrix_led_set(11, 1);

	for( ;; )
	{
		sys_wdt_reset();

		button_proc( sys_timer_get() );
		led_proc( sys_timer_get() );
		led_snake_proc( sys_timer_get() );
		matrix_loop();
	}
}
