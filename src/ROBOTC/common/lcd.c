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

// Define Top Level States
#define STATE_WELCOME 0
#define STATE_AUTO 1
#define STATE_USER 2
#define NUMBER_TOP_STATES 3

#define STR_NEXT_ONLY "           Nxt >"
#define STR_NEXT_PREV "< Prv      Nxt >"
#define STR_NEXT_OK_PREV "< Prv  OK  Nxt >"

#define STR_AUTON "1: Auton Prog"
#define STR_USER "2: User Ctrl"

string lcd_welcome_message;
int current_top_state = STATE_WELCOME;

int prev_buttons[3];
int current_buttons[3];

static void left_button_press();
static void middle_button_press();
static void right_button_press();

// lcd_set_welcome_message: Display the top-level welcome message
//
void lcd_set_welcome_message(string welcome_message)
{
	bLCDBacklight = true;
	lcd_welcome_message = welcome_message;
}

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

	default:
		displayLCDCenteredString(0, "Error:");
		displayLCDCenteredString(1, "Unidentified Top State");
		break;

	}
}

static void left_button_press()
{
	// TODO: Implement
	current_top_state = (current_top_state+NUMBER_TOP_STATES-1) % NUMBER_TOP_STATES;
}

static void middle_button_press()
{
	// TODO: Implement
}

static void right_button_press()
{
	// TODO: Implement
	current_top_state = (current_top_state+1) % NUMBER_TOP_STATES;
}
