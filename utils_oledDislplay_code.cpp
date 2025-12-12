// utils_oledDisplay_code.cpp
#include "utils_oledDisplay_header.h"
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 22
#define OLED_SCL 23
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

namespace OledDisplay {

  Adafruit_SSD1306* display = nullptr; // Referncia interna
  DisplayWrapper displayRef; // Referencia del wrapper global

  bool init() {

    Wire.begin(OLED_SDA, OLED_SCL);

    display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

    if(!display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
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
