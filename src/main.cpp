#include <Wire.h>
#include <Arduino.h>
#include <FastLED.h>
#include <robot.h>

const uint8_t NUM_LEDS = 8;
CRGB leds[NUM_LEDS];

bool state = true;

void setup() {
    Wire.begin();
    Wire.setClock(3400000);
    Serial.begin(115200);

    Robot::begin();
}

void loop() {
    Robot::Sensor::Color m = Robot::Sensor::C(Robot::Sensor::FM);
    Robot::Sensor::Color l = Robot::Sensor::C(Robot::Sensor::FL);
    Robot::Sensor::Color r = Robot::Sensor::C(Robot::Sensor::FR);


    Serial.print(l.to_string());
    // Robot::logln("(%d %d) (%d %d)", l.Redread.Red, l.Redread.Green, l.Greenread.Red, l.Greenread.Green);
    Robot::logln("(%d %d) (%d %d) (%d %d) (%d %d)",
            l.Redread.Red, l.Greenread.Red,
            l.Redread.Green, l.Greenread.Green,
            l.Redread.Blue, l.Greenread.Blue,
            l.Redread.White, l.Greenread.White);
    Serial.print(r.to_string());
    Robot::logln("(%d %d) (%d %d) (%d %d) (%d %d)",
            r.Redread.Red, r.Greenread.Red,
            r.Redread.Green, r.Greenread.Green,
            r.Redread.Blue, r.Greenread.Blue,
            r.Redread.White, r.Greenread.White);
    // Serial.println(l.to_string() + " " + m.to_string() + " " + r.to_string());

// Serial.println(Robot::Sensor::C(0).to_string() + " " +  Robot::Sensor::C(1).to_string() + " " +  Robot::Sensor::C(2).to_string());
// Serial.println(Robot::Sensor::C(3).to_string() + " " +  Robot::Sensor::C(4).to_string() + " " +  Robot::Sensor::C(5).to_string());
// Serial.println(Robot::Sensor::C(6).to_string() + " " +  Robot::Sensor::C(7).to_string() + " " +  Robot::Sensor::C(8).to_string());
Robot::logln("\n\n\n\n\n\n\n");

    // if (l.W() && r.W()) {
    //     Robot::move(255, 255);
    // } else if (l.B() && r.W()) {
    //     Robot::move(255, -255);
    // } else if (l.W() && r.B()) {
    //     Robot::move(-255, 255);
    // } else {
    // }


}
