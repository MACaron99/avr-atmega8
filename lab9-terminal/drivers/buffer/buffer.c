#include <stdint.h>
#include "buffer.h"



int8_t buffer_is_empty( buffer_t *buf )
{
	return buf->size == 0;
}


int8_t buffer_is_full( buffer_t *buf )
{
	return buf->size == BUFFER_SIZE;
}


int8_t buffer_put( buffer_t *buf, uint8_t byte )
{
	if( buffer_is_full(buf) )
	{
		return 0;
	}

	buf->data[buf->tail] = byte;
	buf->tail = (buf->tail + 1) & (BUFFER_SIZE - 1);
	buf->size++;
	return 1;
}


int8_t buffer_get( buffer_t *buf, uint8_t *byte )
{
	if( buffer_is_empty(buf) )
	{
		return 0;
	}

	*byte = buf->data[buf->head];
	buf->head = (buf->head + 1) & (BUFFER_SIZE - 1);
	buf->size--;
	return 1;
}


void buffer_init( buffer_t *buf )
{
	buf->head = 0;
	buf->tail = 0;
	buf->size = 0;
}
