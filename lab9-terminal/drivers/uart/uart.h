#ifndef UART_H
#define UART_H



int8_t uart_get( uint8_t *byte );
int8_t uart_put( uint8_t byte );
void uart_proc( void );
void uart_init( void );

#endif
