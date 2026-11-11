#include "Lcd.h"

Lcd::Lcd(byte address, short cols, short rows)
    : cols(cols), rows(rows), i2cAddress(address), displayedText(""),
      lcd(address, cols, rows) {
  
  this->lcd.init();
}

void Lcd::setText(const String& text) {
  this->displayedText = text;
  int start = 0;
  for (short row = 0; row < this->rows; row++) {
    String line = "";
    if (start >= 0) {
      const int end = text.indexOf('\n', start);
      line = (end < 0) ? text.substring(start) : text.substring(start, end);
      start = (end < 0) ? -1 : end + 1;
    }
    while ((short)line.length() < this->cols) {
      line += ' ';
    }
    this->lcd.setCursor(0, row);
    this->lcd.print(line.substring(0, this->cols));
  }
}

String Lcd::getText() {
  return this->displayedText;
}

void Lcd::turnOn() {
  this->lcd.display();
  this->lcd.backlight();
}

void Lcd::turnOff() {
  this->lcd.noBacklight();
  this->lcd.noDisplay();
}