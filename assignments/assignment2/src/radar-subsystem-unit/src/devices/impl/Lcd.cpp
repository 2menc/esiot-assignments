#include "Lcd.h"

Lcd::Lcd(byte address, short cols, short rows)
    : cols(cols), rows(rows), i2cAddress(address), displayedText(""),
      lcd(address, cols, rows), message('\0') {
  
  this->lcd.init();
  this->lcd.backlight();
}

void Lcd::setText(const String& text) {
  this->lcd.setCursor(0, 0);

  this->message = text;
  this->lcd.print(this->message);
}

String Lcd::getText() {
  return this->message;
}
