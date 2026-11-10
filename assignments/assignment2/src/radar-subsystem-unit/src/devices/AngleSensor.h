#ifndef __ANGLE_SENSOR__
#define __ANGLE_SENSOR__

/** An input device whose position is read as an angle. */
class AngleSensor {
public:
  virtual ~AngleSensor() {}

  /** @return the current angle, from 0 to 180 degrees */
  virtual int getAngle() = 0;
};

#endif
