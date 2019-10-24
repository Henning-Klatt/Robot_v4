#include <Arduino.h>

#include "veml.h"

VemlArray array;

void setup()
{
    Serial.begin(9600);
    array.begin(VEML6040_IT_40MS);
}

void loop()
{
    Serial.print(array[0].Red);
    Serial.print(" ");
    Serial.print(array[0].Green);
    Serial.print(" ");
    Serial.println(array[0].Blue);
    delay(100);
}
