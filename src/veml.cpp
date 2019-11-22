#include "Wire.h"
#ifndef __MATH_H
#include <math.h>
#endif

#include "veml.h"
// #include "log.h"

bool VEML6040::begin(void)
{
    bool sensorExists;
    Wire.begin();
    Wire.beginTransmission(VEML6040_I2C_ADDRESS);
    if (Wire.endTransmission() == 0) {
        sensorExists = true;
    }
    return sensorExists;
}

void VEML6040::setConfiguration(uint8_t configuration)
{
    Wire.beginTransmission(VEML6040_I2C_ADDRESS);
    Wire.write(COMMAND_CODE_CONF);
    Wire.write(configuration);
    Wire.write(0);
    Wire.endTransmission();
    lastConfiguration = configuration;
}

uint16_t VEML6040::read(uint8_t commandCode)
{
    uint16_t data = 0;

    Wire.beginTransmission(VEML6040_I2C_ADDRESS);
    Wire.write(commandCode);
    Wire.endTransmission(false);
    Wire.requestFrom(VEML6040_I2C_ADDRESS, 2);
    while (Wire.available()) {
        data = Wire.read();
        data |= Wire.read() << 8;
    }

    return data;
}

uint16_t VEML6040::getRed(void)
{
    return (read(COMMAND_CODE_RED));
}

uint16_t VEML6040::getGreen(void)
{
    return (read(COMMAND_CODE_GREEN));
}

uint16_t VEML6040::getBlue(void)
{
    return (read(COMMAND_CODE_BLUE));
}

uint16_t VEML6040::getWhite(void)
{
    return (read(COMMAND_CODE_WHITE));
}

float VEML6040::getAmbientLight(void)
{
    uint16_t sensorValue;
    float ambientLightInLux;

    sensorValue = read(COMMAND_CODE_GREEN);

    switch (lastConfiguration & 0x70) {
    case VEML6040_IT_40MS:
        ambientLightInLux = sensorValue * VEML6040_GSENS_40MS;
        break;
    case VEML6040_IT_80MS:
        ambientLightInLux = sensorValue * VEML6040_GSENS_80MS;
        break;
    case VEML6040_IT_160MS:
        ambientLightInLux = sensorValue * VEML6040_GSENS_160MS;
        break;
    case VEML6040_IT_320MS:
        ambientLightInLux = sensorValue * VEML6040_GSENS_320MS;
        break;
    case VEML6040_IT_640MS:
        ambientLightInLux = sensorValue * VEML6040_GSENS_640MS;
        break;
    case VEML6040_IT_1280MS:
        ambientLightInLux = sensorValue * VEML6040_GSENS_1280MS;
        break;
    default:
        ambientLightInLux = -1;
        break;
    }
    return ambientLightInLux;
}

uint16_t VEML6040::getCCT(float offset)
{
    uint16_t red, blue, green;
    float cct, ccti;

    red = read(COMMAND_CODE_RED);
    green = read(COMMAND_CODE_GREEN);
    blue = read(COMMAND_CODE_BLUE);

    ccti = ((float)red - (float)blue) / (float)green;
    ccti = ccti + offset;
    cct = 4278.6 * pow(ccti, -1.2455);

    return ((uint16_t)cct);
}

void VemlArray::begin(uint8_t config)
{
    Wire.begin();
    sensor.setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);

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

struct Color VemlArray::operator[](int index)
{
    selectSensor(index);
    struct Color c;

    c.Red = sensor.getRed();
    c.Green = sensor.getGreen();
    c.Blue = sensor.getBlue();
    c.White = sensor.getWhite();
    c.AL = sensor.getAmbientLight();
    c.CCT = sensor.getCCT();

    return c;
}
