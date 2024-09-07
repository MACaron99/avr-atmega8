#include <system.h>
#include <string.h>
#include "drivers/button/button.h"
#include "drivers/led/led.h"
#include "drivers/matrix/matrix.h"
#include "drivers/multiplexer/multiplexer.h"
#include "drivers/uart/uart.h"
#include "drivers/timer/timer.h"
#include "drivers/shell/shell.h"


int8_t help_cmd( int8_t arg );
int8_t ledon_cmd( int8_t led );
int8_t ledoff_cmd( int8_t led );


cmd_t cmd_table[] =
{
	{ "help", help_cmd },

	{ "ledon", ledon_cmd },

	{ "ledoff", ledoff_cmd },

	{ 0, 0 }
};



int8_t help_cmd( int8_t arg )
{
	if( arg )
	{
		shell_help();
	}

	return arg;
}


int8_t ledon_cmd( int8_t led )
{
	if( led > 0 && led < 16 )
	{
		matrix_led_set(led - 1, 1);
		return 1;
	}

	return 0;
}


int8_t ledoff_cmd( int8_t led )
{
	if( led > 0 && led < 16 )
	{
		matrix_led_set(led - 1, 0);
		return 1;
	}

	return 0;
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
	uart_init();
	shell_init(cmd_table);

	sys_int_enable();

	for( ;; )
	{
		sys_wdt_reset();

		button_proc();
		led_proc();
		led_snake_proc();
//		multi_proc();
		matrix_proc();
		uart_proc();
		shell_proc();
	}
}
