#include "Lcd.h"

Lcd::Lcd(byte address, short cols, short rows)
    : cols(cols), rows(rows), i2cAddress(address), displayedText(""),
      lcd(address, cols, rows) {
}

void Lcd::setText(const String& text) {
}

String Lcd::getText() {
  return displayedText;
}
