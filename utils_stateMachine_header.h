// utils_stateMachine_header.h
#ifndef UTILS_STATE_MACHINE_HEADER_H
#define UTILS_STATE_MACHINE_HEADER_H

#include <Arduino.h>

typedef void (*StateEnterFunc)();
typedef void (*StateUpdateFunc)();
typedef void (*StateExitFunc)();

struct State {
  const char* name;
  StateEnterFunc enter;
  StateUpdateFunc update;
  StateExitFunc exit;
  bool canSleep = false;
};

void handleInactivity();

namespace StateMachine {

  void registerState(State s);
  void changeState(const char* name);
  void init();
  void update();
  
}   

#endif
