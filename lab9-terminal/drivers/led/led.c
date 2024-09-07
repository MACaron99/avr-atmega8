#include <avr/io.h>
#include "led.h"
#include "../timer/timer.h"



void led_proc( void )
{
	static uint8_t led_state;
	static uint16_t timer;

	if( (sys_timer_get() - timer) < 2000 )
	{
		return;
	}
	timer = sys_timer_get();

	led_state = !led_state;

	if( led_state )
	{
		PORTB |= (1 << 5);
	}
	else
	{
		PORTB &= ~(1 << 5);
	}
}


void led_snake_proc( void )
{
	static int8_t stage;
	static uint16_t timer;

	switch (stage)
	{
	case 0:
		PORTB &= ~(1 << 2);
		PORTB |= (1 << 4);

		if( (sys_timer_get() - timer) >= 10000 )
		{
			timer = sys_timer_get();
			stage++;
		}
		break;

	case 1:
		PORTB &= ~(1 << 4);
		PORTB |= (1 << 3);

		if( (sys_timer_get() - timer) >= 10000 )
		{
			timer = sys_timer_get();
			stage++;
		}
		break;

	case 2:
		PORTB &= ~(1 << 3);
		PORTB |= (1 << 2);

		if( (sys_timer_get() - timer) >= 10000 )
		{
			timer = sys_timer_get();
			stage = 0;
		}
		break;
	}
}
