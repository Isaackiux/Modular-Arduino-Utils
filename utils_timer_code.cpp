// utils_timer_code.cpp
#include "utils_timer_header.h"
#include <map>

static std::map<String, unsigned long> timers;
static std::map<String, unsigned long> durations;

namespace Timer {

  // Inicia un timer solo si NO existe
  void start(const char* id, unsigned long duration) {
    String key = String(id);
    if (!timers.count(key)) {
      timers[key] = millis();
      durations[key] = duration;
    }
  }

  // Verifica si terminó
  bool finished(const char* id) {
    String key = String(id);
    if (!timers.count(key)) return false;
    return (millis() - timers[key] >= durations[key]);
  }

  // Borra el timer (para poder usarlo de nuevo, o solo dejar limpio el map)
  void remove(const char* id) {
    String key = String(id);
    timers.erase(key);
    durations.erase(key);
  }
}
