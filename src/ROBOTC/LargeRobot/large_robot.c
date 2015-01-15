#pragma config(UART_Usage, UART1, uartUserControl, baudRate115200, IOPins, None, None)
#pragma config(Sensor, in1,    pot_left,       sensorPotentiometer)
#pragma config(Sensor, in2,    pot_right,      sensorPotentiometer)
#pragma config(Motor,  port1,           RightLift1,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           LeftLift1,     tmotorVex393, openLoop)
#pragma config(Motor,  port3,           Intake,        tmotorVex393, openLoop)
#pragma config(Motor,  port4,           FrontRight,    tmotorVex393, openLoop)
#pragma config(Motor,  port5,           FrontLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port6,           LeftLift2,     tmotorVex393, openLoop)
#pragma config(Motor,  port7,           RightLift2,    tmotorVex393, openLoop)
#pragma config(Motor,  port8,           Strafe,        tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           BackLeft,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          BackRight,     tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////
//
//	FILE: large_robot.c
//	ORIGINAL AUTHOR: MH1613
//	DESCRIPTION: This file is a ROBOTC file, based on the competition control template
// 	from Vex Robotics. It defines how the robot should behave in autonomous mode without
//  user input, and how controls sent remotely should be interpreted.
//
//    MOTOR CONFIGURATION <NEW>
//			1. Right Lift 1								6. Left Lift 2
//			2. Left Lift 1								7. Right Lift 2
//			3. Intake (Y Cable)						8. Strafe (Y Cable)
//			4. Right Front Drive					9. Left Rear Drive
//			5. Left Front Drive						10. Right Rear Drive
//
//		COMMS CONFIGURATION
//
//			UART1. BeagleBone Link
//			UART2. LCD Screen
//			I2C.   Backup BeagleBone Link
//
//		SENSOR CONFIGURATION
//
//			1. (Analog) Left Lift Potentiometer
//			2. (Analog) Right Lift Potentiometer
//		TODO Rotary Encoders.
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

int max(int a, int b) {
	return a > b ? a : b;
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

	int left_pot = 0, right_pot = 0, prev_left_pot, prev_right_pot;
	prev_left_pot = 1426 - SensorValue[pot_left];
	prev_right_pot = SensorValue[pot_right] - 777;

	int state_requested_lift_direction = 0; // 0 for up, 1 for still, 2 for down
	int base_lift_power = 100;
	int lift_power_multiplier = 1;

	while (true)
	{
		lcd_poll();

		/* Begin our lift checking and potentiometer
		* - Normalise our pot measurements
		* - Compare with previous pot measurements for our differential
		* - Differential gives speed, so adjust base motor power and difference multiplier to compensate
		* - Apply motor power based on user input, difference between pot positions and differential state
		* - Check limits to ensure the lift does not attempt to move past top/bottom of robot
		*/

		// Left pot start position is 1426, moving downwards
		int left_pot = 1426 - SensorValue[pot_left];

		// Right pot start position is 777, moving upwards
		int right_pot = SensorValue[pot_right] - 777;
		//writeDebugStreamLine("Left: %d; Right: %d.", left_pot, right_pot);

		state_requested_lift_direction = vexRT[Btn5D] - vexRT[Btn5U] + 1;


		int left_lift_rate, right_lift_rate;
		if (abs(right_pot - left_pot) < 500) {
			switch (vexRT[Btn5D] - vexRT[Btn5U]) {
				// 1 is down
				case 1:
					left_lift_rate = 127 - (max(0, right_pot - left_pot) * 3);
					right_lift_rate = 127 - (max(0, left_pot - right_pot) * 3);
					break;
				// 0 is straighten up
				case 0:
					left_lift_rate = (left_pot - right_pot) * 1;
					right_lift_rate = (right_pot - left_pot) * 1;
					break;
				// -1 is up
				case -1:
					left_lift_rate = (max(0, left_pot - right_pot) * 3) - 127;
					right_lift_rate = (max(0, right_pot - left_pot) * 3) - 127;
					break;
			}
		} else {
			// Assume we've reached here because motors have cut.
			motor[FrontLeft] = 0;
			motor[FrontRight] = 0;
			motor[BackLeft] = 0;
			motor[BackRight] = 0;
			motor[Strafe] = 0;
			left_lift_rate = 0;
			right_lift_rate = 0;
			wait1Msec(3000); // Time for motors to come back
		}

		int rightDrive = (-vexRT[Ch3] + vexRT[Ch4]); // Left/Right motors
		int leftDrive = (-vexRT[Ch3] - vexRT[Ch4]);

		if (!direction){
	  rightDrive = -rightDrive;
	  leftDrive = -leftDrive;
		}
		motor[FrontLeft] = leftDrive;
		motor[BackLeft] = leftDrive;
		motor[BackRight] = rightDrive;
		motor[FrontRight] = rightDrive;

		motor[Intake] = (vexRT[Btn6D] - vexRT[Btn6U]) * 127;

		motor[LeftLift1] = left_lift_rate;
		motor[RightLift1] = right_lift_rate;
		motor[LeftLift2] = left_lift_rate;
		motor[RightLift2] = right_lift_rate;

		motor[Strafe] = vexRT[Ch1];

		update_direction(state_direction, direction);

		wait1Msec(50);
	}
}
