// main.cpp

// Headers y utilidades
#include "utils_stateMachine_header.h"

// Estados
#include "state_generic_header.h"

// ----- SETUP -----
void setup() {

  // Registrar estados (El primer estado que se registra en la maquina de estados, es con el que se inicializara)
  StateMachine::registerState(createGenericState());
  // Aqui se continuan registrando estados...

  // Inicializar la máquina de estados
  StateMachine::init();
}

// ----- LOOP -----
void loop() {
  StateMachine::update(); // Correr la maquina de estados
}
