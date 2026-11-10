#ifndef __BUTTON__
#define __BUTTON__

/** A push button. */
class Button {
public:
  virtual ~Button() {}

  /** @return true while the button is held down */
  virtual bool isPressed() = 0;
};

#endif
