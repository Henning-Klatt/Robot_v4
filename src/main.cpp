#include <Wire.h>
#include <Arduino.h>
#include <PrintEx.h>

#include "veml.h"

#define log(fmt) serial.printf("%s:%s - " fmt "\n", __FILE__, __func__);
#define logf(fmt, ...) serial.printf("%s:%s - " fmt "\n", __FILE__, __func__, __VA_ARGS__);

// VemlArray array;
// VEML6040 sensor;
StreamEx serial = Serial;

void setup()
{
    pinMode(2, OUTPUT);
    pinMode(5, OUTPUT);

    digitalWrite(2, LOW);
    digitalWrite(5, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(5, HIGH);

    Wire.begin();
    Serial.begin(9600);
    while(!Serial); 
    log("Initializing...");


    // sensor.setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
    // sensor.begin();
    // log("Initialized Sensor")

    log("Initialized");
}

void loop()
{
    Wire.beginTransmission(MULTIPLEX_I2C_ADDRESS);
    Wire.write(1<<0);
    byte err = Wire.endTransmission();
    logf("Set Multiplexer to ch 0: %d", err);

    if (err != 0) {
        log("I2C error. Aborting...");
        while(1);
    }

    // log("%s", sensor.getRed());
    // Serial.print(array[0].Red);
    // Serial.print(" ");
    // Serial.print(array[0].Green);
    // Serial.print(" ");
    // Serial.println(array[0].Blue);
    // delay(100);
}
