#pragma config(UART_Usage, UART1, uartUserControl, baudRate115200, IOPins, None, None)
#pragma config(Motor,  port1,           FrontLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           BackLeft,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,           BackRight,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           FrontRight,    tmotorVex393, openLoop)
#pragma config(Motor,  port8,           StrafeLeft,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           StrafeRight,   tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           LiftRight1,    tmotorVex393, openLoop)
#pragma config(Motor,  port8,           LiftLeft1,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           LiftRight2,    tmotorVex393, openLoop)
#pragma config(Motor,  port8,           LiftLeft2,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           IntakeLeft,   tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           IntakeRight,    tmotorVex393, openLoop)

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

void update_direction(int &state_direction, int &direction)
{

		switch (state_direction)
		{
			case 0: if (vexRT(Btn7U))
			{
				state_direction = 3;
				direction = 1;
			}
			break;
			case 1: if(!vexRT(Btn7U))
			{
				state_direction = 0;
			}
			break;
			case 2: if(vexRT(Btn7U))
			{
				state_direction = 1;
				direction = 0;
			}
			break;
			case 3: if(!vexRT(Btn7U))
			{
				state_direction = 2;
			}
			break;
			default: state_direction =0;
	 		break;
	}
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
	int state_direction = 0; //3 is reverse & btnhi, 2 is reverse & btnlo, 1 is forward & btnhi, 0 is forward & btnlo : suggested by Erwei
	int direction = 0; // 0 is forward, 1 is reverse

	while (true)
	{
		lcd_poll();

		int rightDrive = (-vexRT[Ch3] + vexRT[Ch1])/2; // Left/Right motors
		int leftDrive = (-vexRT[Ch3] - vexRT[Ch1])/2;

		if (!direction){
	  rightDrive = -rightDrive;
	  leftDrive = -leftDrive;
		}
		motor[FrontLeft] = leftDrive;
		motor[BackLeft] = leftDrive;
		motor[BackRight] = rightDrive;
		motor[FrontRight] = rightDrive;

		motor[IntakeLeft] = (vexRT[Btn6D] - vexRT[Btn6U)) * 127 ;
		motor[IntakeRight] = (vexRT[Btn6D] - vexRT[Btn6U)) * 127 ;

		motor[LiftLeft1] = (vexRT[Btn5D] - vexRT[Btn5U)) * 127 ;
		motor[LiftRight1] = (vexRT[Btn5D] - vexRT[Btn5U)) * 127 ;
		motor[LiftLeft2] = (vexRT[Btn5D] - vexRT[Btn5U)) * 127 ;
		motor[LiftRight2] = (vexRT[Btn5D] - vexRT[Btn5U)) * 127 ;

		motor[StrafeLeft] = vexRT[Ch4];
		motor[StrafeRight] = vexRT[Ch4];

		update_direction(state_direction, direction);

		wait1Msec(50);
	}
}
