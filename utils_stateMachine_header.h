// utils_stateMachine_header.h
#ifndef STATE_MACHINE_HEADER_H
#define STATE_MACHINE_HEADER_H

#include <Arduino.h>

// Las funciones ya NO requieren display obligatoriamente.
// Cada estado decide si usa pantalla o no llamando a Oled::get().
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

namespace StateMachine {
  void handleInactivity();

  void registerState(State s);
  void changeState(const char* name);
  void stateMachineInit();
  void stateMachineUpdate();  
}   

#endif
