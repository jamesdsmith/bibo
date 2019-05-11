#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__
class MotorDriver {
public:
  MotorDriver(int pin1, int pin2);
  void CW();
  void CCW();
  void Stop();
  void Brake();
private:
  int pin1;
  int pin2;
};
#endif
