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

#include "lcd.h"

/////////////////////////////////////////////////////////////////////////////////////////
//
//	LOCAL DEFINITIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

// Define Top Level States
#define STATE_CURRENT 0
#define STATE_AUTO 1
#define STATE_USER 2
#define STATE_BATT 3
#define STATE_CLR 4
#define STATE_RUN 5
#define NUMBER_TOP_STATES 6

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
#define STR_CLR		"4: Set Colour"
#define STR_RUN		"5: Run Auton"

#define STR_CONFIRMED "Confirmed"
#define STR_RETURN "Back To Top"

/////////////////////////////////////////////////////////////////////////////////////////
//
//	LOCAL VARIABLES
//
/////////////////////////////////////////////////////////////////////////////////////////

// Local LCD variables
int current_top_state = STATE_CURRENT;
int current_sub_state = 0;

int prev_buttons[3];
int current_buttons[3];

// Tracks whether we are in top state or sub state
bool sub_state = false;

// Variables for auton programs/user configs
char* auton_progs[MAX_AUTON_PROGS];
char* user_configs[MAX_USER_CONFIGS];
int number_autonomous_programs = 0;
int number_user_configs = 0;
int selected_auto_prog = 0;
int selected_user_conf = 0;
int selected_colour = 0; // 0 blue, 1 red
bool run_auton = false;

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

// lcdTask: Read inputs and implement state machine
void lcdTask(void* ignore) {

	lcdSetBacklight(uart2, true);
	int buttons_pressed = 0;

	while (1) {
		lcdClear(uart2);

		// Check for button presses
		buttons_pressed = lcdReadButtons(uart2);
		current_buttons[0] = (buttons_pressed & LCD_BTN_LEFT) > 0;
		current_buttons[1] = (buttons_pressed & LCD_BTN_CENTER) > 0;
		current_buttons[2] = (buttons_pressed & LCD_BTN_RIGHT) > 0;

		// Compare with previous
		// Left button press
		if (prev_buttons[0] && !current_buttons[0]) {
			left_button_press();
		}
		// Right Button Press
		if (prev_buttons[2] && !current_buttons[2]) {
			right_button_press();
		}
		// Middle Button Press
		if (prev_buttons[1] && !current_buttons[1]) {
			middle_button_press();
		}

		prev_buttons[0] = current_buttons[0];
		prev_buttons[1] = current_buttons[1];
		prev_buttons[2] = current_buttons[2];

		if (!sub_state) {
			// In top level state, display top level menu
			switch (current_top_state) {
			case STATE_CURRENT:
				lcdPrint(uart2, 1, "Current: %s",
						selected_colour == 0 ? "Blue" : "Red");
				if (number_autonomous_programs > 0) {
					lcdSetText(uart2, 2, auton_progs[selected_auto_prog]);
				} else {
					lcdSetText(uart2, 2, "No Auton Prog");
				}
				break;

			case STATE_AUTO:
				lcdSetText(uart2, 1, STR_AUTON);
				lcdSetText(uart2, 2, STR_NEXT_OK_PREV);
				break;

			case STATE_USER:
				lcdSetText(uart2, 1, STR_USER);
				lcdSetText(uart2, 2, STR_NEXT_OK_PREV);
				break;

			case STATE_BATT:
				lcdSetText(uart2, 1, STR_BATT);
				lcdSetText(uart2, 2, STR_NEXT_OK_PREV);
				break;

			case STATE_CLR:
				lcdSetText(uart2, 1, STR_CLR);
				lcdSetText(uart2, 2, STR_NEXT_OK_PREV);
				break;

			case STATE_RUN:
				lcdSetText(uart2, 1, STR_RUN);
				lcdSetText(uart2, 2, STR_NEXT_OK_PREV);
				break;

			default:
				lcdSetText(uart2, 1, "Error:");
				lcdSetText(uart2, 2, "Unidentified Top State");
				break;
			}
		} else {
			// In sub state, decide on submenu to display and get string
			// 0 is return to previous menu, so it is always the same
			if (current_sub_state == 0) {
				lcdSetText(uart2, 1, STR_RETURN);
				lcdSetText(uart2, 2, STR_NEXT_OK_PREV);
			} else {
				switch (current_top_state) {
				case STATE_AUTO:
					lcdSetText(uart2, 1, auton_progs[current_sub_state - 1]);
					lcdSetText(uart2, 2, STR_NEXT_OK_PREV);
					break;
				case STATE_USER:
					lcdSetText(uart2, 1, user_configs[current_sub_state - 1]);
					lcdSetText(uart2, 2, STR_NEXT_OK_PREV);
					break;
				case STATE_BATT:
					if (current_sub_state == 1) {
						lcdPrint(uart2, 1, "Primary: %1.2fV", powerLevelMain() / 1000.0);
					} else if (current_sub_state == 2) {
						lcdPrint(uart2, 1, "Backup: %1.2fV", powerLevelBackup() / 1000.0);
					}
					lcdSetText(uart2, 2, STR_NEXT_OK_PREV);
					break;
				case STATE_CLR:
					if (current_sub_state == 1) {
						lcdSetText(uart2, 1, "Blue");
					}
					if (current_sub_state == 2) {
						lcdSetText(uart2, 1, "Red");
					}
					lcdSetText(uart2, 2, STR_NEXT_OK_PREV);
					break;
				}
			}
		}

		delay(50);

	}
}

// lcd_add_auton_prog: Add the given string as an autonomous program for selection
bool lcd_add_auton_prog(char* auton_prog_name) {
	if (number_autonomous_programs == MAX_AUTON_PROGS) {
		return false;
	} else {
		auton_progs[number_autonomous_programs++] = auton_prog_name;
	}
	return true;
}

// lcd_add_user_config: Add the given string as a user configuration for selection
bool lcd_add_user_config(char* user_conf_name) {
	if (number_user_configs == MAX_USER_CONFIGS) {
		return false;
	} else {
		user_configs[number_user_configs++] = user_conf_name;
	}
	return true;
}

// lcd_get_auton_prog: Get the selected autonomous program ID
int lcd_get_auton_prog() {
	return selected_auto_prog;
}

// lcd_get_user_conf: Get the selected user configuration ID
int lcd_get_user_conf() {
	return selected_user_conf;
}

int lcd_get_colour() {
	return selected_colour;
}

bool lcd_auton_requested() {
	bool ret = run_auton;
	if (ret == true) {
		run_auton = false;
	}
	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	PRIVATE FUNCTION DEFINITIONS
//
/////////////////////////////////////////////////////////////////////////////////////////

// left_button_press: React to the LCD left button being pressed and released
static void left_button_press() {
	if (!sub_state) {
		current_top_state = (current_top_state + NUMBER_TOP_STATES - 1)
				% NUMBER_TOP_STATES;
	} else {
		switch (current_top_state) {
		case STATE_AUTO:
			current_sub_state = (current_sub_state + number_autonomous_programs)
					% (number_autonomous_programs + 1);
			break;
		case STATE_USER:
			current_sub_state = (current_sub_state + number_user_configs)
					% (number_user_configs + 1);
			break;
		case STATE_BATT:
		case STATE_CLR:
			current_sub_state = (current_sub_state + 2) % 3;
			break;
		}
	}
}

// middle_button_press: React to the LCD middle button being pressed and released
static void middle_button_press() {
	if (!sub_state) {
		// If our top state has a sub-menu, go to it
		switch (current_top_state) {
		case STATE_AUTO:
			sub_state = true;
			current_sub_state = number_autonomous_programs > 0;
			break;
		case STATE_USER:
			sub_state = true;
			current_sub_state = number_user_configs > 0;
			break;
		case STATE_BATT:
		case STATE_CLR:
			sub_state = true;
			current_sub_state = 1;
			break;
		case STATE_RUN:
			// Show countdown 3,2,1
			lcdClear(uart2);
			lcdSetText(uart2, 1, "       3        ");
			delay(1000);

			lcdClear(uart2);
			lcdSetText(uart2, 1, "       2        ");
			delay(1000);

			lcdClear(uart2);
			lcdSetText(uart2, 1, "       1        ");
			delay(1000);

			lcdClear(uart2);
			run_auton = true;
			current_top_state = 0;

			break;
		default:
			break;
		}
	}
	// We are already in sub-state, so process
	else {
		// 0 is always go to top-level menu
		if (current_sub_state == 0) {
			sub_state = false;
		} else {
			// Store the selection depending on what's being selected
			// Show confirmation and keep screen on for that set time
			switch (current_top_state) {
			case STATE_AUTO:
				selected_auto_prog = current_sub_state - 1;
				lcdSetText(uart2, 1, STR_CONFIRMED);
				delay(1000);
				lcdClear(uart2);
				sub_state = false;
				current_top_state = 0;
				break;
			case STATE_USER:
				selected_user_conf = current_sub_state - 1;
				lcdSetText(uart2, 1, STR_CONFIRMED);
				delay(1000);
				lcdClear(uart2);
				sub_state = false;
				current_top_state = 0;
				break;
			case STATE_CLR:
				selected_colour = current_sub_state - 1;
				lcdSetText(uart2, 1, STR_CONFIRMED);
				delay(1000);
				lcdClear(uart2);
				sub_state = false;
				current_top_state = 0;
				break;
				// No op for other states
			default:
				break;
			}
		}
	}
}

// right_button_press: React to the LCD right button being pressed and released
static void right_button_press() {
	if (!sub_state) {
		current_top_state = (current_top_state + 1) % NUMBER_TOP_STATES;
	} else {
		switch (current_top_state) {
		case STATE_AUTO:
			current_sub_state = (current_sub_state + 1)
					% (number_autonomous_programs + 1);
			break;
		case STATE_USER:
			current_sub_state = (current_sub_state + 1)
					% (number_user_configs + 1);
			break;
		case STATE_BATT:
		case STATE_CLR:
			current_sub_state = (current_sub_state + 1) % 3;
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	END OF FILE
//
/////////////////////////////////////////////////////////////////////////////////////////
