#include "view.h"

void display_static(String message, short cursor[2]);
void display_rolling(String message);

long lastScrollTime;
bool justStartedRolling = false;

LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);

LiquidCrystal_I2C lcd_init() {
  lcd.init();
  lcd.backlight();

  lastScrollTime = millis();

  return lcd;
}

void display(String message, short cursor[2], DISPLAY_MODE mode) {
  switch (mode) {
    case DISPLAY_STATIC: {
      display_static(message, cursor);
      break;
    }

    case DISPLAY_ROLLING: {
      display_rolling(message);
      break;
    }

    default: return;

  }
}

void display_static(String message, short cursor[2]) {
  lcd.setCursor(cursor[0], cursor[1]);
  lcd.clear();
  lcd.print(message);
}


void display_rolling(String message) {
  long currentScrollTime = millis();
  short currentCursor[2];

  if(justStartedRolling) {
    currentCursor[0] = LCD_WIDTH-1;
    currentCursor[1] = 0;

    justStartedRolling = false;
  }


  if(currentScrollTime - lastScrollTime >= SCROLL_SPEED) {
    currentCursor[0]--;
    lcd.setCursor(currentCursor[0], currentCursor[1]);

    lcd.clear();
    lcd.print(message);
  }
  
  lastScrollTime = currentScrollTime;
}










