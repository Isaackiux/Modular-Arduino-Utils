// utils_buttons_header.h
#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

// Definimos nombres fáciles para los botones
enum ButtonID {
    BTN_SELECT,
    BTN_LEFT,
    BTN_RIGHT,
    BTN_UP,
    BTN_DOWN,
    BTN_BACK,
    BTN_COUNT // Total de botones 
};

namespace Input {
    // Inicializa los pines de cada boton (poner en setup)
    void init();

    // Lee el hardware y actualiza el estado (poner en loop) 
    void update();

    
    // Devuelve true SOLO en el momento exacto que se presiona
    bool isPressed(ButtonID btn);

    // Devuelve true mientras el botón se mantenga presionado
    bool isHeld(ButtonID btn);

    // Devuelve true si se preciono algun boton
    bool anyKey();

    // Devuelve el respectivo pin del ButtonID ingresado
    int getButtonPin(ButtonID btn);
}

#endif