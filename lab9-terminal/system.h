#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

#define PIN_SET(ARGS)                  __SET_PIN(ARGS)
#define PIN_CLR(ARGS)                  __CLR_PIN(ARGS)
#define PIN_TOGGLE(ARGS)               __TOGGLE_PIN(ARGS)
#define PIN_STATE(ARGS)                __PIN_STATE(ARGS)
#define __SET_PIN(PORT_LETTER, N   )   PORT ## PORT_LETTER |=  ( 1 << N )
#define __CLR_PIN(PORT_LETTER, N)      PORT ## PORT_LETTER &= ~( 1 << N )
#define __TOGGLE_PIN(PORT_LETTER, N)   PORT ## PORT_LETTER ^=  ( 1 << N )
#define __PIN_STATE(PORT_LETTER, N)    ( PIN ## PORT_LETTER & ( 1 << N ) )



#define sys_int_enable()            __asm__ __volatile__ ("sei" ::)
#define sys_int_disable()           __asm__ __volatile__ ("cli" ::)

#define sys_wdt_reset()             __asm__ __volatile__ ("wdr")
#if   defined (__AVR_ATmega8__) || defined (__AVR_ATmega128__)
#define sys_wdt_enable()            do {                                 \
                                    __asm__ __volatile__ ("wdr");        \
	                                WDTCR  = (1 << WDCE) | (1 << WDE);   \
	                                WDTCR  = (1 << WDE)  | (1 << WDP2) | \
	                                         (1 << WDP1) | (1 << WDP0);  \
                                       } while(0)
#define sys_powerdown_cpu()         do {                                       \
	                                MCUCR |= ( 1 << SM1) | (1 << SE);          \
	                                __asm__ __volatile__ ( "sleep" "\n\t" :: );\
                                       } while(0)
#elif defined (__AVR_ATmega168__) || defined (__AVR_ATmega168P__) || \
	  defined (__AVR_ATmega88__)
#define sys_wdt_enable()            do {                                 \
                                    __asm__ __volatile__ ("wdr");        \
	                                WDTCSR = (1 << WDCE) | (1 << WDE);   \
	                                WDTCSR = (1 << WDE)  | (1 << WDP2) | \
	                                         (1 << WDP1) | (1 << WDP0);  \
                                       } while(0)
#define sys_powerdown_cpu()         do {                                       \
	                                SMCR  |= (1 << SM1) | (1 << SE);           \
	                                __asm__ __volatile__ ( "sleep" "\n\t" :: );\
                                       } while(0)
#else
	#error "<system.h> - Unknown MCU type"
#endif


#endif
