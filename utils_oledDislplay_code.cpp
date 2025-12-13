// utils_oledDisplay_code.cpp
#include "utils_oledDisplay_header.h"
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 22
#define OLED_SCL 23
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// -------------------------
//  IMPLEMENTACIÓN WRAPPER
// -------------------------
DisplayWrapper::DisplayWrapper() : disp(nullptr) {} // Constructor

void DisplayWrapper::set(Adafruit_SSD1306* d) {
  disp = d;
}

// Passthrough completo de funciones usadas
void DisplayWrapper::clearDisplay()                 { disp->clearDisplay(); }
void DisplayWrapper::display()                      { disp->display(); }
void DisplayWrapper::invertDisplay(bool i)          { disp->invertDisplay(i); }

void DisplayWrapper::drawBitmap(int16_t x, int16_t y,
                                const uint8_t bitmap[], 
                                int16_t w, int16_t h,
                                uint16_t color) {
  disp->drawBitmap(x, y, bitmap, w, h, color);
}

void DisplayWrapper::drawLine(int16_t x0, int16_t y0,
                              int16_t x1, int16_t y1,
                              uint16_t color) {
  if (disp) {
    disp->drawLine(x0, y0, x1, y1, color);
  }
}

void DisplayWrapper::setCursor(int16_t x, int16_t y) { disp->setCursor(x, y); }
void DisplayWrapper::setTextSize(uint8_t size)       { disp->setTextSize(size); }
void DisplayWrapper::setTextColor(uint16_t color)    { disp->setTextColor(color); }
void DisplayWrapper::setFont(const GFXfont* f)       { disp->setFont(f); }

size_t DisplayWrapper::print(const char* s)          { return disp->print(s); }
size_t DisplayWrapper::println(const char* s)        { return disp->println(s); }

void DisplayWrapper::getTextBounds(
    const char* text, int16_t x, int16_t y,
    int16_t* x1, int16_t* y1, uint16_t* w, uint16_t* h
) {
  disp->getTextBounds(text, x, y, x1, y1, w, h);
}

int16_t DisplayWrapper::width()  { return disp->width(); }
int16_t DisplayWrapper::height() { return disp->height(); }


// -------------------------
//  SISTEMA DE DISPLAY GLOBAL
// -------------------------
namespace OledDisplay {

  Adafruit_SSD1306* display = nullptr; // Referencia interna
  DisplayWrapper displayRef;           // Referencia del wrapper global

  bool init() {

    Wire.begin(OLED_SDA, OLED_SCL);

    display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

    if (!display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println("OLED DISPLAY CAN'T INITIALIZE");
      delete display;
      display = nullptr;
      return false;
    }

    displayRef.set(display); // Conectar el wrapper a la referencia interna

    display->clearDisplay();
    display->display();
    return true;
  }

  bool isAvailable() {
    return display != nullptr;
  }

}
