#ifndef __SCREEN__
#define __SCREEN__

#include <Arduino.h>

/** A display able to show a line of text. */
class Screen {
public:
  virtual ~Screen() {}

  /**
   * Replaces the displayed text.
   * @param text text to show
   */
  virtual void setText(const String& text) = 0;

  /** @return the text currently displayed */
  virtual String getText() = 0;

  virtual void turnOn() = 0;
  virtual void turnOff() = 0;
};

#endif
