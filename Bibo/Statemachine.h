#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__
class Statemachine {
public:
  void input(int val);
  bool changed();
private:
  int oldVal;
  bool stateChanged;
};
#endif
