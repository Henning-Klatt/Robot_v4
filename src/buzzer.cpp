#include "buzzer.h"

void beginBuzzer() {
    pinMode(BUZZER_PIN, OUTPUT);
}

void buzz(unsigned int frequency, unsigned long duration) {
    tone(BUZZER_PIN, frequency, duration);
}

void buzz(unsigned int frequency) {
    buzz(frequency, 30);
}
