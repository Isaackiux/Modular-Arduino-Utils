// utils_timer_header.h
#ifndef UTILS_TIMER_H
#define UTILS_TIMER_H

#pragma once
#include <Arduino.h>

namespace Timer {
  void start(const char* id, unsigned long duration);  // Inicia timer solo si NO existe
  bool finished(const char* id);                       // Ya termino?
  void remove(const char* id);                         // Borrar timer
}


#endif
