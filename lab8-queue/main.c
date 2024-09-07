
#include <system.h>
#include "drivers/button/button.h"
#include "drivers/led/led.h"
#include "drivers/matrix/matrix.h"
#include "drivers/multiplexer/multiplexer.h"
#include "drivers/uart/uart.h"
#include "drivers/timer/timer.h"


#define MESSAGE1                                200
#define MESSAGE2                                15


void io_init( void )
{
	DDRB |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
	DDRC |= (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
	DDRD |= (1 << 2) | (1 << 3) | (1 << 6) | (1 << 7);

	PORTC |= (1 << 5);
}


void app_terminal( void )
{
	static int8_t stage;
	static uint16_t timer;


	switch( stage )
	{
	case 0:
		if (sys_timer_get() - timer >= 10000)
		{
			timer = sys_timer_get();
			stage++;
		}
		break;

	case 1:
		if( uart_put( MESSAGE1 ) )
		{
			stage++;
		}
		break;

	case 2:
		if( uart_put( MESSAGE2 ) )
		{
			stage++;
		}
		break;

	case 3:
		stage = 0;
		break;
	}
}


void main( void ) __attribute__ ((noreturn));
void main( void )
{
	sys_wdt_enable();
	io_init();
	sys_timer_init();
	uart_init();
	sys_int_enable();

	for( ;; )
	{
		sys_wdt_reset();

		button_proc();
		led_proc();
		led_snake_proc();
		multi_proc();
		matrix_proc();

//		app_terminal();
		uart_proc();
	}
}
