#include "Statemachine.h"

void Statemachine::input(int val) {
  if (oldVal != val) {
    stateChanged = true;
  }
  oldVal = val;
}

bool Statemachine::changed() {
  if (stateChanged) {
    stateChanged = false;
    return true;
  }
  return false;
}
