#ifndef __VIEW__
#define __VIEW__

#include <LiquidCrystal_I2C.h> 
#include "Arduino.h"

#define LCD_WIDTH 16
#define LCD_HEIGHT 2

#define SCROLL_SPEED 300 //ms

extern LiquidCrystal_I2C lcd;

typedef enum {
  DISPLAY_STATIC,
  DISPLAY_ROLLING
} DISPLAY_MODE;

LiquidCrystal_I2C lcd_init();

void display(String message, short cursor[2], DISPLAY_MODE mode);
void lcd_clear();

#endif