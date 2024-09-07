#include <avr/io.h>
#include "button.h"
#include "../timer/timer.h"



void button_proc( void )
{
	static uint16_t timer;

	if( (sys_timer_get() - timer) < 10 )
	{
		return;
	}
	timer = sys_timer_get();

	button_loop();
}


void button_loop( void )
{
	static int8_t stage;
	static uint8_t led_state;
	static uint8_t btn_prev_state;
	static uint8_t state_counter;
	uint8_t btn_state;

	btn_state = !(PINC & (1 << 5));

	if( btn_prev_state == btn_state )
	{
		state_counter++;
		if( state_counter > 20 )
		{
			state_counter = 0;

			switch (stage)
			{
			case 0:
				if( btn_state )
				{
					stage = 1;
				}
				break;

			case 1:
				led_state = !led_state;

				if( led_state )
				{
					PORTC |= (1 << 4);
				}
				else
				{
					PORTC &= ~(1 << 4);
				}
				stage = 2;
				break;

			case 2:
				if( !btn_state )
				{
					stage = 0;
				}
				break;
			}
		}
	}
	btn_prev_state = btn_state;
}
