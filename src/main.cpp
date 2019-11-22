#include <Wire.h>
#include <Arduino.h>

#include "veml.h"
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

    array.begin(VEML6040_IT_40MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);

    log("Initialized");
}

void loop()
{
    logf("%d %d %d %d %d %d", array[0].Red, array[0].Green, array[0].Blue, array[0].White,0, array[0].CCT);
    delay(10);
}


