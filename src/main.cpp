#include <Wire.h>
#include <Arduino.h>

#include "color.h"
#include "log.h"
#include "motor.h"
#include "buzzer.h"

VemlArray array;

void setup() {
    Wire.begin();
    Serial.begin(9600);

    while(!Serial); 
    log("Initializing...");

    beginBuzzer();
    beginMotor();

    array.begin(VEML6040_IT_160MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);

    log("Initialized");
}

void loop() {
    color_t l = array[0];
    color_t r = array[2];

    logf("%d %d %d %d %f %d", l.Red, l.Green, l.Blue, l.White, l.AL, l.CCT);

    if (l.W() && r.W()) {
        move(255, 255);
    } else if (l.B() && r.W()) {
        move(255, -255);
    } else if (l.W() && r.B()) {
        move(-255, 255);
    } else {
    }

    delay(100);
}

