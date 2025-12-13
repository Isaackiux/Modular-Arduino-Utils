// utils_stateMachine_code.cpp
#include "utils_stateMachine_header.h"
#include "utils_buttons_header.h" // Este header solo se nececita para el control de inactividad (solo se usa en la funcion handleInactivity())

#define MAX_STATES 10

static State states[MAX_STATES];
static int stateCount = 0;

static State* currentState = nullptr;
static State* nextState = nullptr;

// Variables de control para Inactividad
static bool inactivityEnabled = true;
static unsigned long inactivityTimeout = 3000; // 5min = 300000, 1min = 60000
static unsigned long lastActivityTime = 0;

// Funcion para el control se Inactividad
void handleInactivity() {
  if(!currentState) return;

  if(Input::anyKey()) {
    lastActivityTime = millis();
    return;
  }

  if(currentState->canSleep) {
    if(millis() - lastActivityTime > inactivityTimeout) {
      StateMachine::changeState("lightSleep");
      lastActivityTime = millis();
    }
  }
}

namespace StateMachine {

  // Funcion para registrar un estado (se registran los estados en el setup del main, el primero que se registra es el estado con el que se inicializa)
  void registerState(State s) {
    if(stateCount < MAX_STATES) states[stateCount++] = s;
  }

  static State* findStateByName(const char* name) {
    for(int i=0; i<stateCount; i++)
      if(strcmp(states[i].name, name) == 0)
        return &states[i];
    return nullptr;
  }

  // Funcion para cambiar de estado
  void changeState(const char* name) {
    nextState = findStateByName(name);
  }

  // Funcion para inicializar la maquina de estados
  void init() {
    if(stateCount > 0) {
      currentState = &states[0];
      if(currentState->enter) currentState->enter();
    }
    lastActivityTime = millis();
  }

  // Funcion para actualizar la maquina de estados (esta funcion va en el loop del main)
  void update() {
    if(nextState) {
      if(currentState && currentState->exit) currentState->exit();
      currentState = nextState;
      nextState = nullptr;
      if(currentState->enter) currentState->enter();
      lastActivityTime = millis();
    }

    if(currentState && currentState->update) currentState->update();

    handleInactivity(); // Comentar esta linea si no se requiere un sistema de Inactividad
  }

}
