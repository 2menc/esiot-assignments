#include "Lcd.h"

Lcd::Lcd(byte address, short cols, short rows)
    : cols(cols), rows(rows), i2cAddress(address), displayedText(""),
      lcd(address, cols, rows) {
  
  this->lcd.init();
}

void Lcd::setText(const String& text) {
  this->displayedText = text;

  int start = 0;
  for (short row = 0; row < this->rows && row < MAX_LCD_ROWS; row++) {
    // take the text of this row, up to the next '\n'
    String line = "";
    if (start >= 0) {
      const int end = text.indexOf('\n', start);
      line = (end < 0) ? text.substring(start) : text.substring(start, end);
      start = (end < 0) ? -1 : end + 1;
    }
    if ((short)line.length() > this->cols) {
      line = line.substring(0, this->cols);
    }

    // the I2C display is slow: skip the rows that did not change
    if (line == this->shownRows[row]) {
      continue;
    }

    // pad with spaces only as far as the old text, to cover it
    String padded = line;
    while (padded.length() < this->shownRows[row].length()) {
      padded += ' ';
    }
    this->lcd.setCursor(0, row);
    this->lcd.print(padded);
    this->shownRows[row] = line;
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
  this->lcd.clear();
  // the screen is now empty: the next setText must write every row
  for (short row = 0; row < MAX_LCD_ROWS; row++) {
    this->shownRows[row] = "";
  }
}