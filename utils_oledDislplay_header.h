// utils_oledDisplay_header.h
#ifndef UTILS_OLED_DISPLAY_H
#define UTILS_OLED_DISPLAY_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// -----------------------------------------------------------
// Wrapper que permite usar la referencia global desde cualquier .cpp que tenga incluido este header
// -----------------------------------------------------------
class DisplayWrapper {
  public:
    DisplayWrapper();                      // Constructor vacio
    DisplayWrapper(Adafruit_SSD1306* disp); // Constructor normal

    void set(Adafruit_SSD1306* d);         // Conectar el display REAL

    // --- Passthrough completo (solo las funciones que usas) ---
    void clearDisplay();
    void display();
    void invertDisplay(bool i);

    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                    int16_t w, int16_t h, uint16_t color);

    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

    void setCursor(int16_t x, int16_t y);
    void setTextSize(uint8_t size);
    void setTextColor(uint16_t color);
    void setFont(const GFXfont* f = nullptr);
    size_t print(const char* s);
    size_t println(const char* s);

    void getTextBounds(const char* text, int16_t x, int16_t y,
                       int16_t* x1, int16_t* y1, uint16_t* w, uint16_t* h);

    int16_t width();
    int16_t height();

  private:
    Adafruit_SSD1306* disp;
};

// -----------------------------------------------------------
// Namespace que expone la pantalla global
// -----------------------------------------------------------
namespace OledDisplay {

  bool init();                 // Inicializa pantalla
  bool isAvailable();          // Devuelve si hay pantalla o no

  extern DisplayWrapper displayRef; // Referencia global
}

#endif
