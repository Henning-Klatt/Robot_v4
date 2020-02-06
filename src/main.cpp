#include <Wire.h>
#include <Arduino.h>
#include <robot.h>
#include <sensor.h>

const uint8_t slow = 50;
const uint8_t normal = 100;
const uint8_t fast = 254;

using namespace Robot;
using namespace Robot::Sensor;

void setup() {
    Wire.begin();
    Wire.setClock(400000);
    Serial.begin(9600);

    Robot::begin();
}

void loop() {
    refresh();
        // Serial.println(C[FL].name);
    // if (C[MM].B && C[FM].B) {
    //     move(normal, normal);
    //     return;
    // }
    //
    // move(slow, slow);
    //
    // if (C[ML].B && !C[BR].B) {
    //     for(; !C[FM].B; refresh()) {
    //         move(-slow, slow);
    //     }
    // } else if (C[BR].B && !C[BL].B) {
    //     for(; !C[FM].B; refresh()) {
    //         move(slow, -slow);
    //     }
    // }
}
