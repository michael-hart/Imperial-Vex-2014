/////////////////////////////////////////////////////////////////////////////////////////
//
//	FILE: uart.c
//	ORIGINAL AUTHOR: MH1613
//	DESCRIPTION: This file is a ROBOTC source file. It allows input and output to and
//  from UART1 on the Vex Cortex Microprocessor. This is vital for communication with
//	the processor providing directions to the cortex.
//  This file is common to both the large and the small robot.
//
/////////////////////////////////////////////////////////////////////////////////////////

#define PACKET_SIZE 5
#define QUEUE_LIMIT 30
#define TIMEOUT_MS 100
#define HEARTBEAT_PERIOD 30

#define TX_HEARTBEAT 0x01
#define TX_LEFT_ENCODER 0x02
#define TX_RIGHT_ENCODER 0x04
#define TX_ACKNOWLEDGE 0x08
#define TX_WAKE_UP 0x10

#define RX_HEARTBEAT 0x01
#define RX_FORWARD 0x02
#define RX_ROTATE 0x04
#define RX_ACKNOWLEDGE 0x08
#define RX_LIFT_HEIGHT 0x10
#define RX_SCORE 0x20

typedef struct {
	byte data[PACKET_SIZE];
	bool ack;
} packet;

typedef struct {
	packet original;
	unsigned long time_sent;
} check_packet;

string current_message;
packet rx_msg_queue[QUEUE_LIMIT];
packet rx_buf;
packet tx_msg_queue[QUEUE_LIMIT];
check_packet tx_ack_queue[QUEUE_LIMIT];

int rx_queue_size = 0, tx_queue_size = 0;
int rx_buf_size = 0, tx_buf_size = 0;
int rx_packet_count = 0, tx_packet_count = 0;
int tx_ack_queue_size = 0;
int dropped_packets = 0;

unsigned long last_heartbeat_sent = 0;
unsigned long last_heartbeat_rcvd = 0;

static void read_all();
static bool check_fletcher(byte* data, int count, unsigned short checksum);
static void xmit_heartbeat();
static void xmit_acknowledge(byte packet_number);
static short calculate_fletcher_16(byte* data, int count);
static void build_xmit_cmd(byte cmd, byte data, bool ack_required);
static void check_ack_queue();
static void xmit_all();

task uart()
{
	ClearTimer(T1);
	while (true)
	{
		// TODO: read_all();
		// Send our heartbeat
		if (T1 - last_heartbeat_sent > HEARTBEAT_PERIOD)
		{
			xmit_heartbeat();
			last_heartbeat_sent = T1;
		}
		// Check BB heartbeat
		if (T1 - last_heartbeat_rcvd > TIMEOUT_MS)
		{
			// TODO: Handle comms drop
		}
		check_ack_queue();
		xmit_all();
		wait1Msec(10);
	}
}

// uart_poll: Checks for input and returns true if a complete instruction is ready
bool uart_poll()
{
	current_message = "";
	char c = getChar(UART1);

	while (c != 0x100)
	{
		strncatSingleChar(current_message, c, 20);
		c = getChar(UART1);
	}

	return strlen(current_message) != 0;
}

void uart_get_cmd(string **pp_rx)
{
	*pp_rx = &current_message;
}

void uart_xmit(byte* tx, int count)
{
	int i = 0;
	for (i = 0; i < count; i++)
	{
		sendChar(UART1, tx[i]);
	}
}

void uart_xmit_left_encoder(byte data)
{
	build_xmit_cmd(TX_LEFT_ENCODER, data, true);
}

void uart_xmit_right_encoder(byte data)
{
	build_xmit_cmd(TX_RIGHT_ENCODER, data, true);
}

void uart_wake_up_bb()
{
	build_xmit_cmd(TX_WAKE_UP, 0, true);
}

static void read_all()
{
	char c = getChar(UART1);
	while (c != 0x100)
	{
		rx_buf.data[rx_buf_size++] = c;
		if (rx_buf_size > PACKET_SIZE)
		{
			// Check packet is valid
			if (!check_fletcher(rx_buf.data, PACKET_SIZE-2,
				rx_buf.data[PACKET_SIZE-2] << 8
					+ rx_buf.data[PACKET_SIZE-1]))
			{
				dropped_packets++;
			}
			else
			{
				// TODO: Implement
			}
		}
	}
}

static void xmit_heartbeat()
{
	build_xmit_cmd(TX_HEARTBEAT, 0, false);
}

static void xmit_acknowledge(byte packet_number)
{
	build_xmit_cmd(TX_HEARTBEAT, packet_number, false);
}

static void build_xmit_cmd(byte cmd, byte data, bool ack_required)
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

static short calculate_fletcher_16( byte* data, int count )
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

static bool check_fletcher(byte* data, int count, unsigned short checksum)
{
	unsigned short csum;
	csum = calculate_fletcher_16(data, count);
	return csum == checksum;
}

static void check_ack_queue()
{
	int index = 0;
	check_packet temp;
	for (; index < tx_ack_queue_size; index++)
	{
		temp = tx_ack_queue[index];
		if (T1 - temp.time_sent > TIMEOUT_MS)
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
			tx.time_sent = T1;
			tx_ack_queue[tx_ack_queue_size++] = tx;
		}
	}
	tx_queue_size = 0;
}
