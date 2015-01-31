/*
 * uart.h
 *
 *  Created on: 30 Jan 2015
 *      Author: Michael
 */

#ifndef UART_H_
#define UART_H_

#include "main.h"
#include "inttypes.h"

	void uartTask(void *ignore);
	void uart_xmit(uint8_t* tx, int count);
	void uart_xmit_left_encoder(uint8_t data);
	void uart_xmit_right_encoder(uint8_t data);
	void uart_wake_up_bb();
	uint8_t uart_cmd_ready();
	void uart_copy_cmd(uint8_t** cmd_queue, int* bytes_copied, int max_arr_size);

#endif /* UART_H_ */
