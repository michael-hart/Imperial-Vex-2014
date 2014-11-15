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

void lcd_set_welcome_message(string welcome_message);
void lcd_poll();

#include "lcd.c";

#endif // _LCD_H
