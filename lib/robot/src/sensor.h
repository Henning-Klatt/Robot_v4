#ifndef SENSOR_H_
#define SENSOR_H_

#include <Arduino.h>

#include <FastLED.h>

namespace Robot {
    namespace Sensor {
        namespace {
            const uint8_t sensor_i2c_address    = 0x10;
            const uint8_t multiplex_i2c_address = 0x70;
            const uint8_t command_code_conf     = 0x00;
            const uint8_t command_code_red      = 0x08;
            const uint8_t command_code_green    = 0x09;
            const uint8_t command_code_blue     = 0x0a;
            const uint8_t command_code_white    = 0x0b;
            const uint8_t gsens_40ms            = 0.25168;
            const uint8_t gsens_80ms            = 0.12584;
            const uint8_t gsens_160ms           = 0.06292;
            const uint8_t gsens_320ms           = 0.03146;
            const uint8_t gsens_640ms           = 0.01573;
            const uint8_t gsens_1280ms          = 0.007865;
            const uint8_t it_40ms               = 0x00;
            const uint8_t it_80ms               = 0x10;
            const uint8_t it_160ms              = 0x20;
            const uint8_t it_320ms              = 0x30;
            const uint8_t it_640ms              = 0x40;
            const uint8_t it_1280ms             = 0x50;
            const uint8_t trig_disable          = 0x00;
            const uint8_t trig_enable           = 0x04;
            const uint8_t af_auto               = 0x00;
            const uint8_t af_force              = 0x02;
            const uint8_t sd_enable             = 0x00;
            const uint8_t sd_disable            = 0x01;

            const uint8_t num_leds = 16;

            typedef struct Read {
                uint16_t Red;
                uint16_t Green;
                uint16_t Blue;
                uint16_t White;
            } Read;

            CRGB leds[num_leds];

            void select_sensor(uint8_t sensor);
            void set_configuration(uint8_t config);
            uint16_t read(uint8_t);
            void set_led_color(CRGB);
        }

        const uint8_t FR = 1;
        const uint8_t FM = 2;
        const uint8_t FL = 3;
        const uint8_t MR = 4;
        const uint8_t MM = 5;
        const uint8_t ML = 6;
        const uint8_t BR = 7;
        const uint8_t BM = 8;
        const uint8_t BL = 9;

        typedef struct Color {
            bool W;
            bool G;
            bool B;
            String name;
        } Color;

        extern Color C[9];

        void refresh();

        void begin();
        void begin(uint8_t config);
    }
}
#endif
