/*
 * uart.c
 *
 *  Created on: 30 Jan 2015
 *      Author: Michael
 */

#include "main.h"
#include "uart.h"

/////////////////////////////////////////////////////////////////////////////////////////
//
//	LOCAL DEFINITIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

// Define global constants
#define PACKET_SIZE 5
#define QUEUE_LIMIT 30
#define TIMEOUT_MS 100
#define HEARTBEAT_PERIOD 30

// Define Transmit (TX) constants
#define TX_HEARTBEAT 0x01
#define TX_LEFT_ENCODER 0x02
#define TX_RIGHT_ENCODER 0x04
#define TX_ACKNOWLEDGE 0x08
#define TX_WAKE_UP 0x10

// Define Receive (RX) constants
#define RX_HEARTBEAT 0x01
#define RX_FORWARD 0x02
#define RX_ROTATE 0x04
#define RX_ACKNOWLEDGE 0x08
#define RX_LIFT_HEIGHT 0x10
#define RX_SCORE 0x20

/////////////////////////////////////////////////////////////////////////////////////////
//
//	STRUCT DEFINITIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

// packet struct contains 5 bytes of data and ack=true if the packet should be
// acknowledged
typedef struct {
	uint8_t data[PACKET_SIZE];
	uint8_t ack;
} packet;

// check_packet stuct contains a packet that requires acknowledgement, tracking its sent
// time to make sure it is acknowledged
typedef struct {
	packet original;
	unsigned long time_sent;
} check_packet;

/////////////////////////////////////////////////////////////////////////////////////////
//
//	LOCAL VARIABLES
//
/////////////////////////////////////////////////////////////////////////////////////////

// Declare RX/TX buffers
uint8_t rx_msg_queue[QUEUE_LIMIT][2];
packet rx_buf;
packet tx_msg_queue[QUEUE_LIMIT];
check_packet tx_ack_queue[QUEUE_LIMIT];

// Declare int trackers
int rx_queue_size = 0, tx_queue_size = 0;
int rx_buf_size = 0;
int tx_packet_count = 0;
int tx_ack_queue_size = 0;
int dropped_packets = 0;

// Declare heartbeat times, which follow timer T1
unsigned long last_heartbeat_sent = 0;
unsigned long last_heartbeat_rcvd = 0;

// Is the BB online?
uint8_t bb_online = 0;

/////////////////////////////////////////////////////////////////////////////////////////
//
//	PRIVATE FUNCTION DECLARATIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

static void read_all();
static uint8_t check_fletcher(uint8_t* data, int count, uint16_t checksum);
static void xmit_heartbeat();
static void xmit_acknowledge(uint8_t packet_number);
static short calculate_fletcher_16(uint8_t* data, int count);
static void build_xmit_cmd(uint8_t cmd, uint8_t data, uint8_t ack_required);
static void check_ack_queue();
static void xmit_all();

/////////////////////////////////////////////////////////////////////////////////////////
//
//	TASK DEFINITIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

// Continuously checks the UART and stores a queue of commands that require action
void uartTask(void *ignore)
{
	// Clear current UART
	while (!feof(uart1)) {
		fgetc(uart1);
	}
	uint32_t current_time;
	// Continuously check t1
	while (1)
	{
		current_time = millis();
		if (!bb_online)
		{
			uart_wake_up_bb();
			xmit_all();
			read_all();
			// Clear tx buffers to prevent overload on wake up
			tx_queue_size = 0;
			tx_ack_queue_size = 0;
			delay(1000);
			continue;
		}

		read_all();
		// Send our heartbeat
		if (current_time - last_heartbeat_sent > HEARTBEAT_PERIOD)
		{
			xmit_heartbeat();
			last_heartbeat_sent = current_time;
		}
		// Check BB heartbeat
		if (current_time - last_heartbeat_rcvd > TIMEOUT_MS)
		{
			bb_online = false;
		}
		check_ack_queue();
		xmit_all();
		delay(2);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	PUBLIC FUNCTION DEFINITIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

// uart_xmit: Given a pointer to a byte array and the array length, transmits the bytes
// over UART1
void uart_xmit(uint8_t* tx, int count)
{
	int i = 0;
	for (i = 0; i < count; i++)
	{
		fputc(tx[i], uart1);
	}
}

// uart_xmit_left_encoder: Helper method that calls uart_xmit with left_encoder data
void uart_xmit_left_encoder(uint8_t data)
{
	build_xmit_cmd(TX_LEFT_ENCODER, data, true);
}

// uart_xmit_right_encoder: Helper method that calls uart_xmit with right_encoder data
void uart_xmit_right_encoder(uint8_t data)
{
	build_xmit_cmd(TX_RIGHT_ENCODER, data, true);
}

// uart_wake_up_bb: Wake up BeagleBoard with Wake Up command
void uart_wake_up_bb()
{
	build_xmit_cmd(TX_WAKE_UP, 0, false);
}

// uart_cmd_ready: Returns a boolean as to whether there are any commands to
// act on
uint8_t uart_cmd_ready()
{
	return rx_queue_size > 0;
}

// uart_copy_cmd: Fills the cmd_queue with command data, along with the number
// of bytes copied, up to a limit of max_arr_size
void uart_copy_cmd(uint8_t** cmd_queue, int* bytes_copied, int max_arr_size)
{
	*bytes_copied = 0;
	for (int i = 0; i < rx_queue_size; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			**cmd_queue = rx_msg_queue[i][j];
			(*cmd_queue)++;
			(*bytes_copied)++;
		}
		if (*bytes_copied + 2 > max_arr_size)
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	PRIVATE FUNCTION DEFINITIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

// read_all: Checks the UART for complete messages and confirms their checksum. Also
// adds the messages to the queue if they require action
static void read_all()
{
	while (!feof(uart1))
	{
		rx_buf.data[rx_buf_size++] = (uint8_t)(fgetc(uart1) & 0xFF);
		if (rx_buf_size >= PACKET_SIZE)
		{
			rx_buf_size = 0;
			unsigned short checksum = (rx_buf.data[3] << 8)
					+ rx_buf.data[4];
			// Check packet is valid
			if (!check_fletcher(rx_buf.data, PACKET_SIZE-2, checksum))
			{
				dropped_packets++;
				return;
			}
			else
			{
				bb_online = true;
				char command_name=rx_buf.data[0];
				switch (command_name){

					case RX_HEARTBEAT:
						last_heartbeat_rcvd = millis();
						break;

					case RX_FORWARD:
					case RX_ROTATE:
					case RX_SCORE:
					case RX_LIFT_HEIGHT:
						rx_msg_queue[rx_queue_size][0] = rx_buf.data[0];
						rx_msg_queue[rx_queue_size++][1] = rx_buf.data[2];
						xmit_acknowledge(rx_buf.data[1]); //sending acknowledge
						break;

					case RX_ACKNOWLEDGE:
						// Check all commands for ID; Remove packet and break
						// if ID matches
						for (int i = 0; i < tx_ack_queue_size; i++)
						{
							if (tx_ack_queue[i].original.data[1] == rx_buf.data[2])
							{
								tx_ack_queue[i] = tx_ack_queue[tx_ack_queue_size--];
								break;
							}
						}
					break;

				}
			}
		}
	}
}

// xmit_heartbeat: Transmits a heartbeat packet
static void xmit_heartbeat()
{
	build_xmit_cmd(TX_HEARTBEAT, 0, false);
}

// xmit_acknowledge: acknowledges a packet received from the BB
static void xmit_acknowledge(uint8_t packet_number)
{
	build_xmit_cmd(TX_HEARTBEAT, packet_number, false);
}

// build_xmit_cmd: Helper method that fills a byte buffer with the
// command data and calculates a checksum using fletcher-16
static void build_xmit_cmd(uint8_t cmd, uint8_t data, uint8_t ack_required)
{
	packet tx;
	tx.data[0] = cmd;
	tx.data[1] = tx_packet_count++;
	tx_packet_count %= 256;
	tx.data[2] = data;
	short fletcher = calculate_fletcher_16(tx.data, 3);
	tx.data[3] = fletcher >> 8;
	tx.data[4] = fletcher & 0xFF;
	tx.ack = ack_required;
	tx_msg_queue[tx_queue_size++] = tx;
}

// calculate-fletcher-16: Calculates a checksum given a byte
// array and length
static short calculate_fletcher_16( uint8_t* data, int count )
{
	short sum1 = 0;
  short sum2 = 0;
  int index;

  for( index = 0; index < count; ++index )
  {
     sum1 = (sum1 + data[index]) % 255;
     sum2 = (sum2 + sum1) % 255;
  }

  return (sum2 << 8) | sum1;
}

// check_fletcher: Given an existing checksum and the data used to
// calculate it, confirms that the given checksum is identical to the
// calculated one
static uint8_t check_fletcher(uint8_t* data, int count, uint16_t checksum)
{
	unsigned short csum;
	csum = calculate_fletcher_16(data, count);
	return csum == checksum;
}

// check_ack_queue: Iterates over the queue of packets requiring
// acknowledgement, and resends any that have times out
static void check_ack_queue()
{
	int index = 0;
	check_packet temp;
	int current_time;
	for (; index < tx_ack_queue_size; index++)
	{
		temp = tx_ack_queue[index];
		current_time = millis();
		if (current_time - temp.time_sent > TIMEOUT_MS)
		{
			build_xmit_cmd(
				temp.original.data[0],
				temp.original.data[1],
				true);
			temp = tx_ack_queue[tx_ack_queue_size];
			tx_ack_queue[index] = temp;
			index--;
			tx_ack_queue_size--;
		}
	}
}

// xmit_all: Transmits complete packet queue sequentially
static void xmit_all()
{
	int index = 0;
	for (; index < tx_queue_size; index++)
	{
		check_packet tx;
		uart_xmit(tx_msg_queue[index].data, PACKET_SIZE);
		if (tx_msg_queue[index].ack)
		{
			tx.original = tx_msg_queue[index];
			tx.time_sent = millis();
			tx_ack_queue[tx_ack_queue_size++] = tx;
		}
	}
	tx_queue_size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	END OF FILE
//
/////////////////////////////////////////////////////////////////////////////////////////
