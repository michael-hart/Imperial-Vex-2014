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

bool uart_poll();
void uart_get_cmd(string **pp_rx);
void uart_xmit(string tx);

#include "uart.c";

#endif // _UART_H
