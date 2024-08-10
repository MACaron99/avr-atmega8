
#include <system.h>
#include <avr/interrupt.h>



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


void led_proc( void )
{
	static uint8_t led_index;
	static uint16_t timer;

	if( (sys_timer_get() - timer) < 2000 )
		return;
	timer = sys_timer_get();

	led_index = !led_index;

	if (led_index)
		PORTB |= (1 << 5);
	else
		PORTB &= ~(1 << 5);
}


void led_snake_proc( void )
{
	static int8_t snake_index;
	static uint16_t timer;


	switch( snake_index )
	{
		case 0:
			PORTB &= ~(1 << 2);
			PORTB |= (1 << 4);

			if( (sys_timer_get() - timer) >= 10000 )
			{
				timer = sys_timer_get();

				snake_index++;
			}
			break;
		case 1:
			PORTB &= ~(1 << 4);
			PORTB |= (1 << 3);

			if( (sys_timer_get() - timer) >= 10000 )
			{
				timer = sys_timer_get();

				snake_index++;
			}
			break;
		case 2:
			PORTB &= ~(1 << 3);
			PORTB |= (1 << 2);

			if( (sys_timer_get() - timer) >= 10000 )
			{
				timer = sys_timer_get();

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


void matrix_loop( int bit_array[] )
{
	for( uint8_t i = 0; i < 8; i++ )
	{
		if( bit_array[i] )
			PORTC |= (1 << 1);
		else
			PORTC &= ~(1 << 1);

		PORTC |= (1 << 3);
		PORTC &= ~(1 << 3);
	}

	PORTC |= (1 << 2);
	PORTC &= ~(1 << 2);
}


void matrix_proc( void )
{
	int snake_bits[15][8] =
	{
			{ 1, 0, 0, 0, 0, 1, 1, 0 },
			{ 0, 1, 0, 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 1, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 1, 1, 1, 0 },

			{ 0, 0, 0, 0, 1, 1, 0, 1 },
			{ 0, 0, 0, 1, 0, 1, 0, 1 },
			{ 0, 0, 1, 0, 0, 1, 0, 1 },
			{ 0, 1, 0, 0, 0, 1, 0, 1 },
			{ 1, 0, 0, 0, 0, 1, 0, 1 },

			{ 1, 0, 0, 0, 0, 0, 1, 1 },
			{ 0, 1, 0, 0, 0, 0, 1, 1 },
			{ 0, 0, 1, 0, 0, 0, 1, 1 },
			{ 0, 0, 0, 1, 0, 0, 1, 1 },
			{ 0, 0, 0, 0, 1, 0, 1, 1 }
	};

	static uint16_t timer;
	static int8_t snake_stage;

	matrix_loop( snake_bits[snake_stage] );

	if( (sys_timer_get() - timer) >= 2000 )
	{
		timer = sys_timer_get();

		if( snake_stage++ >= 15 )
		{
			snake_stage = 0;
		}
	}
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


	for( ;; )
	{
		sys_wdt_reset();

		led_proc();
		led_snake_proc();
		button_proc();
		matrix_proc();
	}
}
