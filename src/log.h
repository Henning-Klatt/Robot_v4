#ifndef LOG_H_
#define LOG_H_

#include <Arduino.h>

#include <PrintEx.h>

namespace {
    StreamEx serial = Serial;
}


#define log(fmt) serial.printf("%s:%s - " fmt "\n", __FILE__, __func__);
// #define logf(fmt, ...) serial.printf("%s:%s - " fmt "\n", __FILE__, __func__, __VA_ARGS__);
#define logf(fmt, ...) serial.printf(fmt "\n", __VA_ARGS__);


// void log(char fmt[]);
// void logf(char fmt[], char args[]...);

#endif
