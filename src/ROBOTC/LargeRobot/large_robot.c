#pragma config(UART_Usage, UART1, uartUserControl, baudRate115200, IOPins, None, None)
#pragma config(Motor,  port4,           FrontLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           BackLeft,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port6,           BackRight,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           FrontRight,    tmotorVex393, openLoop)
#pragma config(Motor,  port8,           StrafeLeft,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           StrafeRight,   tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////
//
//	FILE: large_robot.c
//	ORIGINAL AUTHOR: MH1613
//	DESCRIPTION: This file is a ROBOTC file, based on the competition control template
// 	from Vex Robotics. It defines how the robot should behave in autonomous mode without
//  user input, and how controls sent remotely should be interpreted.
//
//		MOTOR CONFIGURATION
//
//			1. Left Front Drive	(PE)			6. Right Back Drive
//			2. Right Front Drive					7. Left Back Drive
//			3. Left Lift Upper						8. Left Lift Lower
//			4. Right Lift Upper						9. Right Lift Lower
//			5. Strafe (Both via Y-cable) 10. Intake (Both via Y-cable)
//
//		COMMS CONFIGURATION
//
//			UART1. BeagleBone Link
//			UART2. LCD Screen
//			I2C.   Backup BeagleBone Link
//
//
/////////////////////////////////////////////////////////////////////////////////////////

// Competition includes and defines
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"

// Robot includes and defines
#include "../common/lcd.h"
#include "../common/uart.h"

// Public function definitions

void setup_lcd() {
	lcd_setup();
	// TODO: Add autonomous programs here
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
	StartTask(uart);
	while (true)
	{
		lcd_poll();
		int rightDrive = (-vexRT[Ch3] + vexRT[Ch1])/2; // Left/Right motors
		int leftDrive = (-vexRT[Ch3] - vexRT[Ch1])/2;
		motor[FrontLeft] = leftDrive;
		motor[BackLeft] = leftDrive;
		motor[BackRight] = rightDrive;
		motor[FrontRight] = rightDrive;

		motor[StrafeLeft] = vexRT[Ch4];
		motor[StrafeRight] = vexRT[Ch4];
		wait1Msec(50);
	}
}
