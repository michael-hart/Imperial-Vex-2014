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
#include "Vex_Competition_Includes.c"

// Robot includes and defines
#include "../common/lcd.h"

// Public function definitions

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
	while (true)
	{
	  UserControlCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
	}
}
