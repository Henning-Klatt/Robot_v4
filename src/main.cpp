#include <Wire.h>
#include <Arduino.h>
#include <FastLED.h>

#include "color.h"
//#include "log.h"
#include "motor.h"
#include "buzzer.h"

VemlArray array;

CRGB leds[16];


void setup() {
    FastLED.addLeds<NEOPIXEL, 13>(leds, 16);

    for(byte i = 0; i < 16; i++) {
      leds[i] = CRGB(155,155,155);
    }
    FastLED.show();
    Wire.begin();
    Serial.begin(115200);

    while(!Serial);
    Serial.println("Initializing...");

    beginBuzzer();
    beginMotor();

    array.begin(VEML6040_IT_40MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);

    Serial.println("Initialized");
}

/*
0: Vorne rechts
1: Vorne Mitte
2: Vorne links
3: Mitte rechts
4: Mitte links
5: Hinten rechts
*/


void loop() {
    color_t l = array[2]; // Vorne links
    color_t l1 = array[4];
    color_t r = array[0]; // Vorne rechts
    color_t r1 = array[3];
    color_t m = array[1]; // Vorne Mitte

    //Serial.println(l1.White);


    if ((l.W() && r.W()) || m.B()) {
        move(200, 200);
    } if (l.B() && r.W()) {
        //Serial.println("nach rechts");
        move(-100, 100);
    }

    if (l.W() && r.B()) {
        //Serial.println("nach links");
        move(100, -100);
    }
    /*if (l.W() && m.W() && r1.B()) {
      move(150, -50);
      buzz(433, 500);
    }*/
}
