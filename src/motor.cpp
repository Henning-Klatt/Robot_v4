#include "motor.h"

#include "log.h"

void beginMotor() {
    log("Initializing Motors...");
    pinMode(left_bw, OUTPUT);
    pinMode(right_bw, OUTPUT);
    pinMode(left_fw, OUTPUT);
    pinMode(right_fw, OUTPUT);

    digitalWrite(left_bw, LOW);
    digitalWrite(right_bw, LOW);
    digitalWrite(left_fw, LOW);
    digitalWrite(right_fw, LOW);
}

void move(int left, int right) {
    digitalWrite(left_bw, LOW);
    digitalWrite(right_bw, LOW);
    digitalWrite(left_fw, LOW);
    digitalWrite(right_fw, LOW);

    if (left < 0) {
        digitalWrite(left_fw, LOW);
        analogWrite(left_bw, abs(left));
    } else if (left > 0) {
        digitalWrite(left_bw, LOW);
        analogWrite(left_fw, left);
    } else {
        digitalWrite(left_bw, LOW);
        digitalWrite(left_fw, LOW);
        return;
    }

    if (right < 0) {
        digitalWrite(right_fw, LOW);
        analogWrite(right_bw, abs(right));
    } else if (right > 0) {
        digitalWrite(right_bw, LOW);
        analogWrite(right_fw, right);
    } else {
        digitalWrite(right_bw, LOW);
        digitalWrite(right_fw, LOW);
        return;
    }
}
