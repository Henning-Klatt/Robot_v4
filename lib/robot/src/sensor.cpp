#include "sensor.h"

#include <Wire.h>

#include "robot.h"


namespace Robot {
    namespace Sensor {
        namespace {
            void selectSensor(uint8_t sensor) {
                if (sensor == 5) {
                    digitalWrite(pin_i2c_multiplexer, LOW);
                    digitalWrite(pin_i2c_sensor_5, HIGH);
                } else {
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
                }
            }

            void setConfiguration(uint8_t config) {
                Wire.beginTransmission(sensor_i2c_address);
                Wire.write(command_code_conf);
                Wire.write(config);
                Wire.write(0);
                Wire.endTransmission();
                last_configuration = config;
            }

            float read_AL(void) {
                uint16_t sensorValue;
                float ambientLightInLux;

                sensorValue = read(command_code_green);

                switch (last_configuration & 0x70) {
                    case it_40ms:
                        ambientLightInLux = sensorValue * gsens_40ms;
                        break;
                    case it_80ms:
                        ambientLightInLux = sensorValue * gsens_80ms;
                        break;
                    case it_160ms:
                        ambientLightInLux = sensorValue * gsens_160ms;
                        break;
                    case it_320ms:
                        ambientLightInLux = sensorValue * gsens_320ms;
                        break;
                    case it_640ms:
                        ambientLightInLux = sensorValue * gsens_640ms;
                        break;
                    case it_1280ms:
                        ambientLightInLux = sensorValue * gsens_1280ms;
                        break;
                    default:
                        ambientLightInLux = -1;
                        break;
                }
                return ambientLightInLux;
            }

            uint16_t read_CCT(float offset) {
                uint16_t red, blue, green;
                float cct, ccti;

                red = read(command_code_red);
                green = read(command_code_green);
                blue = read(command_code_blue);

                ccti = ((float)red - (float)blue) / (float)green;
                ccti = ccti + offset;
                cct = 4278.6 * pow(ccti, -1.2455);

                return ((uint16_t)cct);
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
                leds[0] = color;
                leds[1] = color;
                leds[2] = color;
                leds[3] = color;
                leds[4] = color;
                leds[5] = color;
                leds[6] = color;
                leds[7] = color;
                FastLED.show();
            }
        }

        void begin() {
            begin(it_40ms + af_force + sd_enable);
        }

        void begin(uint8_t config) {

            pinMode(pin_i2c_multiplexer, OUTPUT);
            pinMode(pin_i2c_sensor_5, OUTPUT);
            digitalWrite(pin_i2c_multiplexer, HIGH);
            digitalWrite(pin_i2c_sensor_5, LOW);

            for (uint8_t i = 0; i < 8; i++) {
                selectSensor(i);
                setConfiguration(config);
            }
            logln("done");
        }

        Color C(uint8_t sensor) {
            selectSensor(sensor);


            set_led_color(CRGB(100, 0, 0));
            setConfiguration(it_40ms + af_force + sd_enable + trig_enable);
            delay(50);

            Color c;
            c.Redread.Red = read(command_code_red);
            c.Redread.Green = read(command_code_green);
            c.Redread.Blue = read(command_code_blue);
            c.Redread.White = read(command_code_white);
            c.AL = read_AL();
            c.CCT = read_CCT(0);

            set_led_color(CRGB::Green);
            setConfiguration(it_40ms + af_force + sd_enable + trig_disable);
            setConfiguration(it_40ms + af_force + sd_enable + trig_enable);
            delay(50);

            c.Greenread.Red = read(command_code_red);
            c.Greenread.Green = read(command_code_green);
            c.Greenread.Blue = read(command_code_blue);
            c.Greenread.White = read(command_code_white);

            setConfiguration(it_40ms + af_force + sd_enable + trig_disable);

            return c;
        }

        bool Color::W() {
            // return Redread.Red > 1000 && Greenread.Red > 1000;
            return Redread.White > 2000 && Greenread.White > 2000;

        }

        bool Color::G() {
            return Redread.Red < Greenread.Green && !W();
        }

        bool Color::B() {
            return !W();
        }

        bool Color::S() {
            return false;
        }

        String Color::to_string() {
            if (W()) {
                return "White";
            } else if (G()) {
                return "Green";
            } else if (B()) {
                return "Black";
            } else if (W()) {
                return "White";
            } else if (S()) {
                return "Silver";
            }

            return "";
        }
    }
}
