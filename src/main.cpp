#include <Arduino.h>

#include "veml.h"

VemlArray array();

void setup() {
    Serial.begin(9600);
    array.begin();
}

void loop() {
  Serial.println(array[0].Red);
}
