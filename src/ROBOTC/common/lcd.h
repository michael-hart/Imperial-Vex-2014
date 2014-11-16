/////////////////////////////////////////////////////////////////////////////////////////
//
//	FILE: lcd.h
//	ORIGINAL AUTHOR: MH1613
//	DESCRIPTION: This file is a ROBOTC headerfile. It allows input and output to and
//  from an attached LCD screen. This is useful for displaying error messages,
//  determining control styles for the remote control (e.g. inverted analog stick), or
//  selecting a program to run in autonomous mode.
//  This file is common to both the large and the small robot.
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _LCD_H
#define _LCD_H

void lcd_setup();
void lcd_poll();
bool lcd_add_auton_prog(string auton_prog_name);
bool lcd_add_user_config(string user_conf_name);
int lcd_get_auton_prog();
int lcd_get_user_conf();
int lcd_get_colour();
bool lcd_auton_requested();

#include "lcd.c";

#endif // _LCD_H
