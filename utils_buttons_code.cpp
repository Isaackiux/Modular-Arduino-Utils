// utils_buttons_header.h
#include "utils_buttons_header.h"

// --- Configuración de Hardware ---
// El orden debe coincidir con el enum ButtonID en el .h
const int PIN_MAP[BTN_COUNT] = {
    25, // BTN_SELECT
    26, // BTN_LEFT
    27, // BTN_RIGHT
    14, // BTN_UP
    12, // BTN_DOWN
    33  // BTN_BACK
};

// --- Variables Internas ---
struct ButtonObj {
    bool state;       // Estado actual estable
    bool lastState;   // Estado anterior estable
    bool pressed;     // Flag de "se acaba de presionar"
    unsigned long lastDebounceTime;
    bool lastReading; // Lectura cruda anterior
};

static ButtonObj buttons[BTN_COUNT];
static bool _anyKeyPressed = false;
const unsigned long DEBOUNCE_DELAY = 50;

namespace Input {

    void init() {
        for (int i = 0; i < BTN_COUNT; i++) {
            pinMode(PIN_MAP[i], INPUT_PULLUP);
            buttons[i].state = false;
            buttons[i].lastState = false;
            buttons[i].pressed = false;
            buttons[i].lastReading = false;
            buttons[i].lastDebounceTime = 0;
        }
    }

    void update() {
        _anyKeyPressed = false; // Resetear flag global

        for (int i = 0; i < BTN_COUNT; i++) {
            // Resetear flags de evento único
            buttons[i].pressed = false; 

            // Leer hardware (invertido por PULLUP)
            bool reading = !digitalRead(PIN_MAP[i]);

            // Lógica de Debounce
            if (reading != buttons[i].lastReading) {
                buttons[i].lastDebounceTime = millis();
            }
            buttons[i].lastReading = reading;

            if ((millis() - buttons[i].lastDebounceTime) > DEBOUNCE_DELAY) {
                // Si el estado ha cambiado
                if (reading != buttons[i].state) {
                    buttons[i].state = reading;

                    // Si pasó de NO presionado a PRESIONADO
                    if (buttons[i].state == true) {
                        buttons[i].pressed = true;
                        _anyKeyPressed = true; // Hubo actividad
                    }
                }
            }
        }
    }

    bool isPressed(ButtonID btn) {
        return buttons[btn].pressed;
    }

    bool isHeld(ButtonID btn) {
        return buttons[btn].state;
    }

    bool anyKey() {
        return _anyKeyPressed;
    }

    int getButtonPin(ButtonID btn) {
        if(btn < BTN_COUNT) {
            return PIN_MAP[btn];
        }
        return -1;
    }
}