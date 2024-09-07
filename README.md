# AVR ATmega8 Microcontroller Programming Labs

This repository contains a series of lab projects created to learn programming the AVR ATmega8 microcontroller in C. Each lab focuses on a specific topic or peripheral to develop practical skills in embedded system design.

## Lab Projects

1. **Lab1 - LED Control**: 
   - Simple control of an LED connected to the ATmega8 microcontroller.

2. **Lab2 - LED Snake**: 
   - Implementation of a "snake" effect with multiple LEDs.

3. **Lab3 - LED with Button**: 
   - Control an LED with a button input using basic digital I/O.

4. **Lab4 - Matrix LED Snake**: 
   - Create a snake effect on an LED matrix display.

5. **Lab5 - Matrix LED Set**: 
   - Manipulate individual LEDs in an LED matrix.

6. **Lab6 - Multiplexer with Matrix LED**: 
   - Control an LED matrix with a multiplexer.

7. **Lab7 - UART Communication**: 
   - Set up serial communication using UART.

8. **Lab8 - UART with Queue**: 
   - Implement UART communication with a queue for message handling.

9. **Lab9 - UART Terminal**: 
   - Create a terminal interface for UART communication.

## How to Build

Each lab contains its own source files and `Makefile`. To build a specific lab project, navigate to the respective directory and run `make`:

```bash
cd lab1-led
make
```
Ensure you have the necessary AVR toolchain installed, including `avr-gcc` and `avrdude` for compiling and flashing the firmware to the microcontroller.
