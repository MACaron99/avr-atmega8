#ifndef BUFFER_H
#define BUFFER_H


#define BUFFER_SIZE 64


typedef struct
{
	uint8_t data[BUFFER_SIZE];
	uint8_t head;
	uint8_t tail;
	uint8_t size;
} buffer_t;



void buffer_init( buffer_t *buf );
int8_t buffer_is_empty( buffer_t *buf );
int8_t buffer_is_full( buffer_t *buf );
int8_t buffer_put( buffer_t *buf, uint8_t byte );
int8_t buffer_get( buffer_t *buf, uint8_t *byte );

#endif
