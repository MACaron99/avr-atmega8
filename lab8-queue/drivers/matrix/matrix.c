
#include <avr/io.h>
#include "matrix.h"



static int8_t led_array[15];


void matrix_led_set( int8_t led, int8_t state )
{
	led_array[led] = state;
}


void matrix_proc( void )
{
	static uint8_t bit_array[8];
	static int8_t row_index = 0;

	for( uint8_t i = 0; i < 5; i++ )
	{
		bit_array[i] = led_array[i + row_index * 5];
	}

	for( uint8_t i = 0; i < 3; i++ )
	{
		if ( i == row_index )
			bit_array[7 - i] = 0;
		else
			bit_array[7 - i] = 1;
	}

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

	if( ++row_index >= 3 )
		row_index = 0;
}
