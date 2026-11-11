#ifndef __LCD__
#define __LCD__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "../Screen.h"

/** Character LCD connected through the I2C bus. */
class Lcd : public Screen {
private:
  short cols;              /**< number of columns */
  short rows;              /**< number of rows */
  byte i2cAddress;         /**< I2C address of the display */
  String displayedText;    /**< text currently shown */
  LiquidCrystal_I2C lcd;   /**< underlying LCD driver */
  String message;

public:
  /**
   * Creates the LCD and initialises the display.
   * @param address I2C address of the display (usually 0x27)
   * @param cols number of columns
   * @param rows number of rows
   */
  Lcd(byte address, short cols, short rows);

  void setText(const String& text) override;
  String getText() override;
};

#endif
