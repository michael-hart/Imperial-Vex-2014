/////////////////////////////////////////////////////////////////////////////////////////
//
//	FILE: lcd.c
//	ORIGINAL AUTHOR: MH1613
//	DESCRIPTION: This file is a ROBOTC file. It allows input and output to and from an
//  attached LCD screen. This is useful for displaying error messages, determining
//  control styles for the remote control (e.g. inverted analog stick), or selecting a
//  program to run in autonomous mode.
//  This file is common to both the large and the small robot.
//
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//
//	LOCAL DEFINITIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

// Define Top Level States
#define STATE_WELCOME 0
#define STATE_AUTO 1
#define STATE_USER 2
#define STATE_BATT 3
#define NUMBER_TOP_STATES 4

// Define program/config constants
#define MAX_AUTON_PROGS 100
#define MAX_USER_CONFIGS 100

// Define LCD string
#define STR_NEXT_ONLY "           Nxt >"
#define STR_NEXT_PREV "< Prv      Nxt >"
#define STR_NEXT_OK_PREV "< Prv  OK  Nxt >"

#define STR_AUTON "1: Auto Prog"
#define STR_USER  "2: User Ctrl"
#define STR_BATT  "3: Batt Volt"

#define STR_CONFIRMED "Confirmed"
#define STR_RETURN "Back To Top"

/////////////////////////////////////////////////////////////////////////////////////////
//
//	LOCAL VARIABLES
//
/////////////////////////////////////////////////////////////////////////////////////////

// Local LCD variables
string lcd_welcome_message;
int current_top_state = STATE_WELCOME;
int current_sub_state = 0;

int prev_buttons[3];
int current_buttons[3];

// Tracks whether we are in top state or sub state
bool sub_state = false;

// Variables for auton programs/user configs
string auton_progs[MAX_AUTON_PROGS];
string user_configs[MAX_USER_CONFIGS];
int number_autonomous_programs = 0;
int number_user_configs = 0;
int selected_auto_prog = 0;
int selected_user_conf = 0;

/////////////////////////////////////////////////////////////////////////////////////////
//
//	PRIVATE FUNCTION DECLARATIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

static void left_button_press();
static void middle_button_press();
static void right_button_press();

/////////////////////////////////////////////////////////////////////////////////////////
//
//	PUBLIC FUNCTION DEFINITIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

// lcd_set_welcome_message: Display the top-level welcome message
void lcd_set_welcome_message(string welcome_message)
{
	bLCDBacklight = true;
	lcd_welcome_message = welcome_message;
}

// lcd_poll: Read inputs and implement state machine
void lcd_poll()
{
	clearLCDLine(0);
	clearLCDLine(1);

	// Check for button presses
	current_buttons[0] = (nLCDButtons & 1) > 0;
	current_buttons[1] = (nLCDButtons & 2) > 0;
	current_buttons[2] = (nLCDButtons & 4) > 0;

	// Compare with previous
	// Left button press
	if (prev_buttons[0] && !current_buttons[0])
	{
		left_button_press();
	}
	// Right Button Press
	if (prev_buttons[2] && !current_buttons[2])
	{
		right_button_press();
	}
	// Middle Button Press
	if (prev_buttons[1] && !current_buttons[1])
	{
		middle_button_press();
	}

	prev_buttons[0] = current_buttons[0];
	prev_buttons[1] = current_buttons[1];
	prev_buttons[2] = current_buttons[2];

	if (!sub_state)
	{
		// In top level state, display top level menu
		switch (current_top_state)
		{
			case STATE_WELCOME:
				displayLCDCenteredString(0, lcd_welcome_message);
				displayLCDCenteredString(1, STR_NEXT_PREV);
				break;

			case STATE_AUTO:
				displayLCDCenteredString(0, STR_AUTON);
				displayLCDCenteredString(1, STR_NEXT_OK_PREV);
				break;

			case STATE_USER:
				displayLCDCenteredString(0, STR_USER);
				displayLCDCenteredString(1, STR_NEXT_OK_PREV);
				break;

			case STATE_BATT:
				displayLCDCenteredString(0, STR_BATT);
				displayLCDCenteredString(1, STR_NEXT_OK_PREV);
				break;

			default:
				displayLCDCenteredString(0, "Error:");
				displayLCDCenteredString(1, "Unidentified Top State");
				break;
		}
	}
	else
	{
		// In sub state, decide on submenu to display and get string
		// 0 is return to previous menu, so it is always the same
		if (current_sub_state == 0)
		{
				displayLCDCenteredString(0, STR_RETURN);
				displayLCDCenteredString(1, STR_NEXT_OK_PREV);
				return;
		}
		switch(current_top_state)
		{
			case STATE_AUTO:
				displayLCDCenteredString(0, auton_progs[current_sub_state-1]);
				displayLCDCenteredString(1, STR_NEXT_OK_PREV);
				break;
			case STATE_USER:
				displayLCDCenteredString(0, user_configs[current_sub_state-1]);
				displayLCDCenteredString(1, STR_NEXT_OK_PREV);
				break;
			case STATE_BATT:
				// TODO: Battery Voltage
				displayLCDString(0, 0, "Primary: ");
				string mainBattery;
				sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
				displayNextLCDString(mainBattery);
				displayLCDCenteredString(1, STR_NEXT_OK_PREV);
				break;
		}
	}
}

// lcd_add_auton_prog: Add the given string as an autonomous program for selection
bool lcd_add_auton_prog(string auton_prog_name)
{
	if (number_autonomous_programs == MAX_AUTON_PROGS)
	{
		return false;
	}
	else
	{
		auton_progs[number_autonomous_programs++] = auton_prog_name;
	}
	return true;
}

// lcd_add_user_config: Add the given string as a user configuration for selection
bool lcd_add_user_config(string user_conf_name)
{
	if (number_user_configs == MAX_USER_CONFIGS)
	{
		return false;
	}
	else
	{
		user_configs[number_user_configs++] = user_conf_name;
	}
	return true;
}

// lcd_get_auton_prog: Get the selected autonomous program ID
int lcd_get_auton_prog()
{
	return selected_auto_prog;
}

// lcd_get_user_conf: Get the selected user configuration ID
int lcd_get_user_conf()
{
	return selected_user_conf;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	PRIVATE FUNCTION DEFINITIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

// left_button_press: React to the LCD left button being pressed and released
static void left_button_press()
{
	if (!sub_state)
	{
		current_top_state = (current_top_state+NUMBER_TOP_STATES-1) % NUMBER_TOP_STATES;
	}
	else
	{
		switch (current_top_state)
		{
			case STATE_AUTO:
				current_sub_state = (current_sub_state + number_autonomous_programs)
					% (number_autonomous_programs + 1);
				break;
			case STATE_USER:
				current_sub_state = (current_sub_state + number_user_configs)
					% (number_user_configs + 1);
				break;
			case STATE_BATT:
				// 2 allowed states, 0 or 1, so abuse NOT to toggle
				current_sub_state = !current_sub_state;
				break;
		}
	}
}

// middle_button_press: React to the LCD middle button being pressed and released
static void middle_button_press()
{
	if (!sub_state)
	{
		// If our top state has a sub-menu, go to it
		switch (current_top_state)
		{
			case STATE_AUTO:
				sub_state = true;
				current_sub_state = number_autonomous_programs > 0;
				break;
			case STATE_USER:
				sub_state = true;
				current_sub_state = number_user_configs > 0;
				break;
			case STATE_BATT:
				sub_state = true;
				current_sub_state = 1;
				break;
			default:
				break;
		}
	}
	// We are already in sub-state, so process
	else
	{
		// 0 is always go to top-level menu
		if (current_sub_state == 0)
		{
			sub_state = false;
		}
		else
		{
			// Store the selection depending on what's being selected
			// Show confirmation and keep screen on for that set time
			switch (current_top_state)
			{
				case STATE_AUTO:
					selected_auto_prog = current_sub_state - 1;
					displayLCDCenteredString(0, STR_CONFIRMED);
					wait1Msec(1000);
					clearLCDLine(0);
					sub_state = false;
					break;
				case STATE_USER:
					selected_user_conf = current_sub_state - 1;
					displayLCDCenteredString(0, STR_CONFIRMED);
					wait1Msec(1000);
					clearLCDLine(0);
					sub_state = false;
					break;
				// No op for other states
				default:
					break;
			}
		}
	}
}

// right_button_press: React to the LCD right button being pressed and released
static void right_button_press()
{
	if (!sub_state)
	{
		current_top_state = (current_top_state+1) % NUMBER_TOP_STATES;
	}
	else
	{
		switch (current_top_state)
		{
			case STATE_AUTO:
				current_sub_state = (current_sub_state + 1)
					% (number_autonomous_programs + 1);
				break;
			case STATE_USER:
				current_sub_state = (current_sub_state + 1)
					% (number_user_configs + 1);
				break;
			case STATE_BATT:
				// 2 allowed states, 0 or 1, so abuse NOT to toggle
				current_sub_state = !current_sub_state;
				break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	END OF FILE
//
/////////////////////////////////////////////////////////////////////////////////////////
