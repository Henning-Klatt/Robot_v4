#include "sensor.h"

#include <Wire.h>

#include "robot.h"


namespace Robot {
    namespace Sensor {
        namespace {
            void select_sensor(uint8_t sensor) {
                if (sensor == 5) {
                    digitalWrite(pin_i2c_multiplexer, LOW);
                    digitalWrite(pin_i2c_sensor_5, HIGH);
                } else if (sensor > 0 && sensor < 10) {
                    digitalWrite(pin_i2c_multiplexer, HIGH);
                    digitalWrite(pin_i2c_sensor_5, LOW);

                    sensor--;
                    if (sensor > 5) {
                        sensor--;
                    }

                    Wire.beginTransmission(multiplex_i2c_address);
                    Wire.write(1 << sensor);
                    uint8_t result = Wire.endTransmission();
                    if (result != 0) {
                        logln("I2C Error: %d", result);
                    }
                } else {
                    logln("Cannot select sensor (id=%d", sensor);
                }
            }

            void set_configuration(uint8_t config) {
                Wire.beginTransmission(sensor_i2c_address);
                Wire.write(command_code_conf);
                Wire.write(config);
                Wire.write(0);
                Wire.endTransmission();
            }

            uint16_t read(uint8_t commandCode) {
                uint16_t data = 0;

                Wire.beginTransmission(sensor_i2c_address);
                Wire.write(commandCode);
                Wire.endTransmission(false);
                Wire.requestFrom(sensor_i2c_address, 2);
                while (Wire.available()) {
                    data = Wire.read();
                    data |= Wire.read() << 8;
                }

                return data;
            }

            void set_led_color(CRGB color) {
                FastLED.addLeds<NEOPIXEL, pin_neopixel>(leds, num_leds);
                for(int i = 0; i < num_leds; i++){
                  leds[i] = color;
                }
                FastLED.show();
            }
        }

        Color C[9]; // Declare

        void begin() {
            begin(it_40ms + af_force + sd_enable + trig_enable);
        }

        void begin(uint8_t config) {
            pinMode(pin_i2c_multiplexer, OUTPUT);
            pinMode(pin_i2c_sensor_5, OUTPUT);
            digitalWrite(pin_i2c_multiplexer, HIGH);
            digitalWrite(pin_i2c_sensor_5, LOW);

            for (uint8_t i = 0; i < 8; i++) {
                select_sensor(i);
                set_configuration(config);
            }
            logln("done");
        }

        void read_color(Read color[9]) {
            for (uint8_t sensor = 1; sensor <= 9; sensor++) {
                select_sensor(sensor);
                set_configuration(it_40ms + af_force + sd_enable + trig_enable);
                read(command_code_red); // After enabling trigger we have to do an additional I2C connection to trigger it
            }
            delay(40);
            for (uint8_t sensor = 1; sensor <= 9; sensor++) {
                select_sensor(sensor);

                color[sensor-1] = {
                    .Red = read(command_code_red),
                    .Green = read(command_code_green),
                    .Blue = read(command_code_blue),
                    .White = read(command_code_white)
                };
                set_configuration(it_40ms + af_force + sd_enable + trig_disable);
            }
        }

        void refresh() {
            Read red[9], green[9];

            int x = millis();
            set_led_color(CRGB(255, 0, 0));
            delay(9);
            read_color(red);
            set_led_color(CRGB(0,255, 0));
            delay(9);
            read_color(green);
            for (uint8_t sensor = 1; sensor <= 9; sensor++) {
                if (red[sensor-1].White > 4000 && green[sensor-1].White > 4000) {
                    C[sensor-1].name = "WHITE";
                    C[sensor-1].W = true;
                    C[sensor-1].G = false;
                    C[sensor-1].B = false;
                } else if (red[sensor].Red < green[sensor].Green) {
                    C[sensor-1].name = "GREEN";
                    C[sensor-1].W = false;
                    C[sensor-1].G = true;
                    C[sensor-1].B = false;
                } else {
                    C[sensor-1].name = "BLACK";
                    C[sensor-1].W = false;
                    C[sensor-1].G = false;
                    C[sensor-1].B = true;
                }
            }
            Serial.print(C[FL].name);
            Robot::logln(" (%d %d) (%d %d) (%d %d) (%d %d) ", red[FL].Red, green[FL].Red, red[FL].Green, green[FL].Green, red[FL].Blue, green[FL].Blue, red[FL].White, green[FL].White);


        }
    }
}
