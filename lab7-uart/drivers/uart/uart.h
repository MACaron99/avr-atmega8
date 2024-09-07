
#ifndef UART_H
#define UART_H



void uart_init( unsigned int ubrr );
void uart_transmit ( uint16_t sys_timer, unsigned char data );
unsigned char uart_receive( void );

#endif // UART_H
