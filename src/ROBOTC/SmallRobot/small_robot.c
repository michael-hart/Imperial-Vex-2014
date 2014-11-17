/////////////////////////////////////////////////////////////////////////////////////////
//
//	FILE: small_robot.c
//	ORIGINAL AUTHOR: MH1613
//	DESCRIPTION: This file is a ROBOTC file, based on the competition control template
// 	from Vex Robotics. It defines how the robot should behave in autonomous mode without
//  user input, and how controls sent remotely should be interpreted.
//
/////////////////////////////////////////////////////////////////////////////////////////

// Competition includes and defines
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#pragma config(UART_Usage, UART1, uartUserControl, baudRate115200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)
#include "Vex_Competition_Includes.c"

// Robot includes and defines
#include "../common/lcd.h"
#include "../common/uart.h"

// Public function definitions

void setup_lcd() {
	lcd_setup();
	// Save string to variable because ROBOTC sucks
	string s = "Autonomous 1";
	lcd_add_auton_prog(s);
	s = "Autonomous 2";
	lcd_add_auton_prog(s);
	s = "User Conf 1";
	lcd_add_user_config(s);
	s = "User Conf 2";
	lcd_add_user_config(s);
}

// pre_auton: Used to set up the robots with initial servo positions etc. before the
// start of the competition.
void pre_auton()
{
  bStopTasksBetweenModes = true;
}

// autonomous: defines how the robot behaves in autonomous mode.
task autonomous()
{
	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

// usercontrol: Defines how the robot reacts to user input sent from a remote control
task usercontrol()
{
	setup_lcd();
	while (true)
	{
		lcd_poll();
		if (lcd_auton_requested())
		{
			StartTask(autonomous);
		}
		if (uart_poll())
		{
			string rx;
			string **pp_rx = &(&rx);
			uart_get_cmd(pp_rx);
			writeDebugStreamLine(**pp_rx);
		}
		wait1Msec(50);
	}
}
