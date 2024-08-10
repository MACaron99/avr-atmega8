
#include <avr/io.h>
#include "led.h"



void led_proc( uint16_t sys_timer )
{
	static uint8_t led_index;
	static uint16_t timer;

	if( (sys_timer - timer) < 2000 )
		return;
	timer = sys_timer;

	led_index = !led_index;

	if (led_index)
		PORTB |= (1 << 5);
	else
		PORTB &= ~(1 << 5);
}


void led_snake_proc( uint16_t sys_timer )
{
	static int8_t stage;
	static uint16_t timer;


	switch( stage )
	{
		case 0:
			PORTB &= ~(1 << 2);
			PORTB |= (1 << 4);

			if( (sys_timer - timer) >= 10000 )
			{
				timer = sys_timer;

				stage++;
			}
			break;
		case 1:
			PORTB &= ~(1 << 4);
			PORTB |= (1 << 3);

			if( (sys_timer - timer) >= 10000 )
			{
				timer = sys_timer;

				stage++;
			}
			break;
		case 2:
			PORTB &= ~(1 << 3);
			PORTB |= (1 << 2);

			if( (sys_timer - timer) >= 10000 )
			{
				timer = sys_timer;

				stage = 0;
			}
			break;
	}
}
