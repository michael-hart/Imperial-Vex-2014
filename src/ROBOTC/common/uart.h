/////////////////////////////////////////////////////////////////////////////////////////
//
//	FILE: uart.h
//	ORIGINAL AUTHOR: MH1613
//	DESCRIPTION: This file is a ROBOTC headerfile. It allows input and output to and
//  from UART1 on the Vex Cortex Microprocessor. This is vital for communication with
//	the processor providing directions to the cortex.
//  This file is common to both the large and the small robot.
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _UART_H
#define _UART_H

task uart();
void uart_xmit(byte* tx, int count);
void uart_xmit_left_encoder(byte data);
void uart_xmit_right_encoder(byte data);
void uart_wake_up_bb();
bool uart_cmd_ready();
void uart_copy_cmd(byte** cmd_queue, int* bytes_copied, int max_arr_size);

#include "uart.c"

#endif // _UART_H
