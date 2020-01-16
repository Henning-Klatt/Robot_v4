#ifndef BUZZER_H_
#define BUZZER_H_

#include <Arduino.h>

namespace {
    const uint8_t BUZZER_PIN = 11;
}

void beginBuzzer();

void buzz(unsigned int frequency);
void buzz(unsigned int frequency, unsigned long duration);

#endif
