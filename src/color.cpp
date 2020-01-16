#include "color.h"

#include <Wire.h>

#include "log.h"

void VemlArray::begin(uint8_t config)
{
    log("Initializing Veml Array...");

    pinMode(i2c_multiplexer, OUTPUT);
    pinMode(i2c_sensor_5, OUTPUT);
    digitalWrite(i2c_multiplexer, HIGH);
    digitalWrite(i2c_sensor_5, LOW);

    sensor.setConfiguration(config);

    for (uint8_t i = 0; i < 8; i++) {
        if (selectSensor(i) != 0) {
        }
        sensor.begin();
        sensor.setConfiguration(config);
    }
}

uint8_t VemlArray::selectSensor(uint8_t sensor)
{
    Wire.beginTransmission(MULTIPLEX_I2C_ADDRESS);
    Wire.write(1 << sensor);
    return Wire.endTransmission();
}

color_t VemlArray::operator[](int index)
{
    selectSensor(index);

    color_t c = {
        .Red = sensor.getRed(),
        .Green = sensor.getGreen(),
        .Blue = sensor.getBlue(),
        .White = sensor.getWhite(),
        .AL = sensor.getAmbientLight(),
        .CCT = sensor.getCCT()
    };

    return c;
}

bool color_t::B() {
    return color() == 0;
}

bool color_t::G() {
    return color() == 1;
}

bool color_t::W() {
    return color() == 2;
}

bool color_t::S() {
    return color() == 3;
}


uint8_t color_t::color() {
    if (White > 1000) {
        return 2;
    } else {
        return 0;
    }
}
