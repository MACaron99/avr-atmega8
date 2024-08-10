
#include <avr/io.h>
#include <util/delay.h>
#include "multiplexer.h"
#include "../matrix/matrix.h"


#define PB_Y1                       ( 1 << 0 )
#define PB_Y2                       ( 1 << 1 )
#define PD_Y3                       ( 1 << 4 )
#define PD_Y4                       ( 1 << 5 )

#define PD_X1                       ( 1 << 7 )
#define PD_X2                       ( 1 << 6 )
#define PD_X3                       ( 1 << 2 )
#define PD_X4                       ( 1 << 3 )


static int8_t mux_input_state[15];



int8_t mux_input_state_get( int8_t ch )
{
	return mux_input_state[ch];
}


void multi_proc( void )
{
	static int8_t stage;

	switch ( stage )
	{
	case 0:
		PORTD &= ~(PD_X1 | PD_X2);

		_delay_us(1);

		mux_input_state[stage] = (PINB & PB_Y1) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 1:
		PORTD |= (PD_X1 | PD_X2);

		_delay_us(1);

		mux_input_state[stage] = (PINB & PB_Y2) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 2:
		PORTD = (PORTD & ~PD_X1) | PD_X2;

		_delay_us(1);

		mux_input_state[stage] = (PINB & PB_Y2) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 3:
		PORTD = (PORTD & ~PD_X2) | PD_X1;

		_delay_us(1);

		mux_input_state[stage] = (PINB & PB_Y2) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 4:
		PORTD &= ~(PD_X2 | PD_X1);

		_delay_us(1);

		mux_input_state[stage] = (PINB & PB_Y2) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 5:
		PORTD = (PORTD & ~PD_X4) | PD_X3;

		_delay_us(1);

		mux_input_state[stage] = (PIND & PD_Y4) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 6:
		PORTD &= ~(PD_X3 | PD_X4);

		_delay_us(1);

		mux_input_state[stage] = (PIND & PD_Y4) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 7:
		PORTD |= PD_X1 | PD_X2;

		_delay_us(1);

		mux_input_state[stage] = (PINB & PB_Y1) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 8:
		PORTD = (PORTD & ~PD_X1) | PD_X2;

		_delay_us(1);

		mux_input_state[stage] = (PINB & PB_Y1) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 9:
		PORTD = (PORTD & ~PD_X2) | PD_X1;

		_delay_us(1);

		mux_input_state[stage] = (PINB & PB_Y1) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 10:
		PORTD |= PD_X3 | PD_X4;

		_delay_us(1);

		mux_input_state[stage] = (PIND & PD_Y3) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 11:
		PORTD = (PORTD & ~PD_X3) | PD_X4;

		_delay_us(1);

		mux_input_state[stage] = (PIND & PD_Y3) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 12:
		PORTD = (PORTD & ~PD_X4) | PD_X3;

		_delay_us(1);

		mux_input_state[stage] = (PIND & PD_Y3) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 13:
		PORTD &= ~(PD_X3 | PD_X4);

		_delay_us(1);

		mux_input_state[stage] = (PIND & PD_Y3) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage++;
		break;

	case 14:
		PORTD = (PORTD & ~PD_X3) | PD_X4;

		_delay_us(1);

		mux_input_state[stage] = (PIND & PD_Y4) ? 1 : 0;
		matrix_led_set( stage, mux_input_state[stage] );

		stage = 0;
		break;
	}
}
