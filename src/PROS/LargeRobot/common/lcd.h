/*
 * lcd.h
 *
 *  Created on: 31 Jan 2015
 *      Author: Michael
 */

#ifndef LCD_H_
#define LCD_H_

#include "main.h"
#include <stdbool.h>
#include <string.h>

void lcdTask(void* ignore);
bool lcd_add_auton_prog(char* auton_prog_name);
bool lcd_add_user_config(char* user_conf_name);
int lcd_get_auton_prog();
int lcd_get_user_conf();
int lcd_get_colour();
bool lcd_auton_requested();

#endif /* LCD_H_ */
