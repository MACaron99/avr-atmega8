
#include <system.h>
#include <avr/interrupt.h>


volatile uint8_t led5_index = 0;
volatile uint8_t led_index = 0;



void sys_timer_init( void )
{
	TCNT0   = 56;
	TIMSK  |= (1 << TOIE0);
	TCCR0   = (1 << CS01);
}


ISR( TIMER0_OVF_vect )
{
	static uint16_t counter;
	static int8_t snake_index;
	static uint16_t snake_counter;


	TCNT0 = 56;
	counter++;

	if( counter >= 2000 )
	{
		counter = 0;

		led5_index = !led5_index;

		if (led5_index) {
			PORTB |= (1 << 5);
		} else {
			PORTB &= ~(1 << 5);
		}
	}

	snake_counter++;

	switch( snake_index )
	{
		case 0:
			PORTB &= ~(1 << 2);
			PORTB |= (1 << 4);

			if( snake_counter == 10000 )
			{
				snake_counter = 0;
				snake_index++;
			}
			break;
		case 1:
			PORTB &= ~(1 << 4);
			PORTB |= (1 << 3);

			if( snake_counter == 10000 )
			{
				snake_counter = 0;
				snake_index++;
			}
			break;
		case 2:
			PORTB &= ~(1 << 3);
			PORTB |= (1 << 2);

			if( snake_counter == 10000 )
			{
				snake_counter = 0;
				snake_index = 0;
			}
			break;
	}
}


void main( void ) __attribute__ ((noreturn));
void main( void )
{
	sys_wdt_enable();
	sys_timer_init();
	sys_int_enable();

	DDRB |= (1 << 2) | (1 <<3) | (1 << 4) | (1 << 5);

	for( ;; )
	{
		sys_wdt_reset();
	}
}
