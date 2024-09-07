
#include <avr/io.h>
#include "matrix.h"



void matrix_proc( uint16_t sys_timer )
{
	int bits[15][8] =
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
	static int8_t stage;

	matrix_loop( bits[stage] );

	if( (sys_timer - timer) >= 2000 )
	{
		timer = sys_timer;

		if( ++stage >= 15 )
			stage = 0;
	}
}


void matrix_loop( int bits[] )
{
	for( uint8_t i = 0; i < 8; i++ )
	{
		if( bits[i] )
			PORTC |= (1 << 1);
		else
			PORTC &= ~(1 << 1);

		PORTC |= (1 << 3);
		PORTC &= ~(1 << 3);
	}
	PORTC |= (1 << 2);
	PORTC &= ~(1 << 2);
}
