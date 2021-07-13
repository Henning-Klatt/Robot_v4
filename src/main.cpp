#include <Wire.h>
#include <Arduino.h>
#include <FastLED.h>

#include "color.h"
//#include "log.h"
#include "motor.h"
#include "buzzer.h"
#include "notes.h"

VemlArray array;



void setup() {


  randomSeed(analogRead(7));

    int song = random(0,3);

    switch(song){
      case 0:
        tetris();
        break;
      case 1:
        nokia();
        break;
      case 2:
        starwars();
        break;
    }

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
6: Hinten Mitte
*/


void loop() {
    color_t l = array[2]; // Vorne links
    color_t r = array[0]; // Vorne rechts
    color_t m = array[1];
    color_t b = array[6];

    Serial.println(m.White);


    if (m.B()) {
        move(200, 200);
    } if (l.B() && r.W()) {
        //Serial.println("nach rechts");
        move(-100, 100);
    }

    if (l.W() && r.B()) {
        //Serial.println("nach links");
        move(100, -100);
    }

    if (l.W() && m.W() && r.W() && b.B()) {
      move(100, 100);
      delay(200);
      int st = millis();
      while (m.W() && (millis() - st) < 1500) {
        m = array[1];
        move(100, -100);
      }
      if (m.B()) {
        return;
      }
      while (!m.B()) {
        m = array[1];
        move(-100, 100);
      }
    }
}
