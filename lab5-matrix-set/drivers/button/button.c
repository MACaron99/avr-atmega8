
#include <avr/io.h>
#include "button.h"



void button_proc( uint16_t sys_timer )
{
	static uint16_t timer;

	if( (sys_timer - timer) < 10 )
		return;
	timer = sys_timer;

	button_loop();
}


void button_loop( void )
{
	static int8_t stage;
	static uint8_t led_state;
	static uint8_t button_prev_state;
	static uint8_t state_counter;
	uint8_t button_state;

	button_state = !(PINC & (1 << 5));

	if( button_prev_state == button_state )
	{
		state_counter++;
		if( state_counter > 20 )
		{
			state_counter = 0;

			switch( stage )
			{
			case 0:
				if( button_state )
					stage = 1;
				break;

			case 1:
				led_state = !led_state;

				if( led_state )
					PORTC |= (1 << 4);
				else
					PORTC &= ~(1 << 4);
				stage = 2;
				break;

			case 2:
				if( !button_state )
					stage = 0;
				break;
			}
		}
	}
	button_prev_state = button_state;
}
