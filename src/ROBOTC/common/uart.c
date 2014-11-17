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

string current_message;

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

void uart_xmit(string tx)
{
	int i = 0;
	for (i = 0; i < strlen(tx); i++)
	{
		sendChar(UART1, StringGetChar(tx, i));
		while (!bXmitComplete(UART1))
		{
			wait1Msec(10);
		}
	}
}
