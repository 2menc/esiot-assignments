#ifndef __LIGHT__
#define __LIGHT__

/** A light that can be switched on and off. */
class Light {
public:
  virtual ~Light() {}

  /** Switches the light on. */
  virtual void turnOn() = 0;

  /** Switches the light off. */
  virtual void turnOff() = 0;
};

#endif
