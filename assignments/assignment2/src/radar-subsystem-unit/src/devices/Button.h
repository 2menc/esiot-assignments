#ifndef __BUTTON__
#define __BUTTON__

/** A push button. */
class Button {
public:
  virtual ~Button() {}

  /**
   * Tells whether the button has been pressed since the last call.
   * Each press is reported only once.
   * @return true if a new press has occurred
   */
  virtual bool wasPressed() = 0;
};

#endif
