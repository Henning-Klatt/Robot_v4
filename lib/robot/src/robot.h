#ifndef ROBOT_H_
#define ROBOT_H_

#include <Arduino.h>

#include "sensor.h"

namespace Robot {
    namespace { // Constants
        const uint8_t pin_left_fw = 10;
        const uint8_t pin_left_bw = 9;
        const uint8_t pin_right_fw = 3;
        const uint8_t pin_right_bw = 6;
        const uint8_t pin_buzzer = 11;
        const uint8_t pin_i2c_multiplexer = 2;
        const uint8_t pin_i2c_sensor_5 = 5;
        const uint8_t pin_neopixel = 13;
    }

    void begin();
    void log (const char * format, ... );
    void logln (const char * format, ... );
    void move(int left, int right);
    void buzz(unsigned int frequency, unsigned long duration);
    void buzz(unsigned int frequency);
}

#endif 
