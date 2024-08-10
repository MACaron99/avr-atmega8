
#include <system.h>
#include <avr/interrupt.h>



volatile uint16_t led5_counter;
volatile uint16_t snake_counter;
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

	led5_counter++;

	snake_counter++;

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


void led_cycle( void )
{
	static uint8_t led5_index;

	if( led5_counter >= 2000 )
		{
			led5_counter = 0;

			led5_index = !led5_index;

			if (led5_index) {
				PORTB |= (1 << 5);
			} else {
				PORTB &= ~(1 << 5);
			}
		}
}


void snake_cycle( void )
{
	static int8_t snake_index;

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


void button_proc( void )
{
	static int8_t stage;
	static uint8_t led_state;
	static uint8_t button_prev_state;
	static uint8_t state_counter;
	static uint16_t timer;
	uint8_t button_state;


	if( (sys_timer_get() - timer) < 10 )
		return;
	timer = sys_timer_get();


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
				if( !button_state )
				{
					stage = 0;
				}
				break;
			}
		}
	}
	button_prev_state = button_state;
}


void io_init( void )
{
	DDRB |= (1 << 2) | (1 <<3) | (1 << 4) | (1 << 5);

	DDRC |= (1 << 4);

	DDRC &= ~(1 << 5);

	PORTC |= (1 << 5);
}


void main( void ) __attribute__ ((noreturn));
void main( void )
{
	sys_wdt_enable();
	io_init();
	sys_timer_init();
	sys_int_enable();


	for( ;; )
	{
		sys_wdt_reset();

		led_cycle();
		snake_cycle();
		button_proc();
	}
}
