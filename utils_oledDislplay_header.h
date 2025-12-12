// utils_oledDisplay_header.h
#ifndef OLED_DISPLAY_UTILS_H
#define OLED_DISPLAY_UTILS_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// Wrapper que permite usar la referencia global desde cualquier .cpp que tenga incluido este header
class DisplayWrapper {
  Adafruit_SSD1306* ptr = nullptr;
  public:
    void set(Adafruit_SSD1306* p) { ptr = p; }
    bool available() const { return ptr != nullptr; }

    operator Adafruit_SSD1306&() { return *ptr; }
    Adafruit_SSD1306* operator->() { return ptr; }
};

namespace OledDisplay {

  bool init();                 // Inicializa pantalla
  bool isAvailable();          // Devuelve si hay pantalla o no

  extern DisplayWrapper displayRef; // Referencia global
}

#endif
