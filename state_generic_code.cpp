// state_generic_code.cpp
// Aqui agrega tus respectivos #include

// --------------------------------------------------
// Función que se ejecuta al entrar al estado
// --------------------------------------------------
void genericEnter() {

}

// --------------------------------------------------
// Función que se ejecuta en cada actualización del estado
// --------------------------------------------------
void genericUpdate() {
  
}

// --------------------------------------------------
// Función que se ejecuta al salir del estado
// --------------------------------------------------
void mainMenuExit() {

}

// --------------------------------------------------
// Funcion que registra el estado en la Maquina de estados
// --------------------------------------------------
State createGenericState() {
  State s;
  s.name = "generic";
  s.enter = genericEnter;
  s.update = genericUpdate;
  s.exit = genericExit;
  // s.canSleep = true; // Comenta o quita esta linea si no llamas el sistema de inactividad 
  return s;
}
