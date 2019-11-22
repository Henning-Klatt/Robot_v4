#ifndef LOG_H_
#define LOG_H_

#include <PrintEx.h>
#include <Arduino.h>

#define log(fmt) serial.printf("%s:%s - " fmt "\n", __FILE__, __func__);
// #define logf(fmt, ...) serial.printf("%s:%s - " fmt "\n", __FILE__, __func__, __VA_ARGS__);
#define logf(fmt, ...) serial.printf(fmt "\n", __VA_ARGS__);

StreamEx serial = Serial;

#endif
