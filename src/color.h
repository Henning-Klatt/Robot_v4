#ifndef COLOR_H_
#define COLOR_H_

#include <Arduino.h>
#include "veml.h"

namespace {
    const uint8_t i2c_multiplexer = 2;
    const uint8_t i2c_sensor_5 = 5;
};

typedef struct { 
    uint16_t Red;
    uint16_t Green;
    uint16_t Blue;
    uint16_t White;
    float    AL;
    uint16_t CCT;

    bool B();
    bool G();
    bool W();
    bool S();
private:
    uint8_t color();
} color_t;

class VemlArray {
private:
    VEML6040 sensor;
    uint8_t selectSensor(uint8_t sensor);
public:
    void begin(uint8_t config);
    color_t operator[](int index);
};

#endif
