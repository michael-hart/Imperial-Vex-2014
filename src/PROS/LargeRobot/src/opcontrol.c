/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "../common/uart.h"
#include "../common/lcd.h"

#define SENSOR_POT_LEFT 1
#define SENSOR_POT_RIGHT 2
#define MOTOR_LIFT_RIGHT_1 1
#define MOTOR_LIFT_LEFT_1 2
#define MOTOR_INTAKE 3
#define MOTOR_FRONT_RIGHT 4
#define MOTOR_FRONT_LEFT 5
#define MOTOR_LIFT_LEFT_2 6
#define MOTOR_LIFT_RIGHT_2 7
#define MOTOR_STRAFE 8
#define MOTOR_BACK_LEFT 9
#define MOTOR_BACK_RIGHT 10

static int max(int a, int b);
static void update_direction(int *direction);
static void update_lift_rates(int *left, int *right);

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {

	// Motor/Sensor variable declarations
	int direction = 1;
	int rightDrive = 0, leftDrive = 0;
	int left_lift_rate = 0, right_lift_rate = 0;

	printf("Cortex Online\r\n");

	// Create threaded tasks
	taskCreate(uartTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	taskCreate(lcdTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

	// Operator control loop
	while (1) {

		// Wheel motor values
		rightDrive = direction * (-joystickGetAnalog(1, 3) + joystickGetAnalog(1, 4));
		leftDrive = direction * (-joystickGetAnalog(1, 3) - joystickGetAnalog(1, 4));
		motorSet(MOTOR_FRONT_LEFT, leftDrive);
		motorSet(MOTOR_BACK_LEFT, leftDrive);
		motorSet(MOTOR_FRONT_RIGHT, rightDrive);
		motorSet(MOTOR_BACK_RIGHT, rightDrive);

		// Lift motor values
		update_lift_rates(&left_lift_rate, &right_lift_rate);
		motorSet(MOTOR_LIFT_LEFT_1, left_lift_rate);
		motorSet(MOTOR_LIFT_LEFT_2, left_lift_rate);
		motorSet(MOTOR_LIFT_RIGHT_1, right_lift_rate);
		motorSet(MOTOR_LIFT_RIGHT_2, right_lift_rate);

		// Other motor values
		motorSet(MOTOR_INTAKE, (joystickGetDigital(1, 6, JOY_DOWN) -
				joystickGetDigital(1, 6, JOY_UP)) * 127);
		motorSet(MOTOR_STRAFE, joystickGetAnalog(1, 1));

		// Update reverse toggle on Btn7U
		update_direction(&direction);

		delay(50);
	}
}

static int max(int a, int b) {
	return a > b ? a : b;
}

static void update_direction(int *direction)
{
	static bool prv_btn_val = 0;
	bool btn7u = joystickGetDigital(1, 7, JOY_UP);
	if (btn7u && !prv_btn_val) {
		// Toggle forwards or reverse
		*direction = *direction == -1 ? 1 : -1;
	}
	prv_btn_val = btn7u;
}

static void update_lift_rates(int *left, int *right) {

	// First time set-up on static variables
	static int left_offset = -1;
	static int right_offset = -1;
	if (left_offset == -1) {
		left_offset = analogCalibrate(SENSOR_POT_LEFT);
	}
	if (right_offset == -1) {
		right_offset = analogCalibrate(SENSOR_POT_RIGHT);
	}
	// TODO update function to use PD/PID loop instead of simple positioning
//	static int prev_left_pot = left_offset - analogRead(SENSOR_POT_LEFT);
//	static int prev_right_pot = analogRead(SENSOR_POT_RIGHT) - right_offset;

	int left_pot, right_pot;

	left_pot = left_offset - analogRead(SENSOR_POT_LEFT);
	right_pot = analogRead(SENSOR_POT_RIGHT) - right_offset;
	//printf("Left: %d; Right: %d.", left_pot, right_pot);

	if (abs(right_pot - left_pot) > 500) {
		*left = 0;
		*right = 0;
		// Give time for motors to return
		delay(3000);
		return;
	}

	switch (joystickGetDigital(1, 5, JOY_DOWN) - joystickGetDigital(1, 5, JOY_UP)) {
		// 1 is down
		case 1:
			*left = 127 - (max(0, right_pot - left_pot) * 3);
			*right = 127 - (max(0, left_pot - right_pot) * 3);
			break;
		// 0 is straighten up
		case 0:
			*left = (left_pot - right_pot) * 1;
			*right = (right_pot - left_pot) * 1;
			break;
		// -1 is up
		case -1:
			*left = (max(0, left_pot - right_pot) * 3) - 127;
			*right = (max(0, right_pot - left_pot) * 3) - 127;
			break;
	}

}
