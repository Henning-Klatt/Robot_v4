#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>

namespace {
    const uint8_t left_fw = 10;
    const uint8_t left_bw = 9;
    const uint8_t right_fw = 3;
    const uint8_t right_bw = 6;
}

void beginMotor();

void move(int left, int right);

#endif
