#include <robot.h>

namespace Robot {
    void log ( const char * format, ... ) {
        char buffer[256];
        va_list args;
        va_start (args, format);
        vsprintf (buffer,format, args);
        Serial.print(buffer);
        va_end (args);
    }

    void logln(const char *format, ...) {
        char buffer[256];
        va_list args;
        va_start (args, format);
        vsprintf (buffer,format, args);
        Serial.println(buffer);
        va_end (args);
    }

    void begin() {
        logln("Initializing...");

        log("Initializing motors... ");
        pinMode(pin_left_bw, OUTPUT);
        pinMode(pin_right_bw, OUTPUT);
        pinMode(pin_left_fw, OUTPUT);
        pinMode(pin_right_fw, OUTPUT);
        digitalWrite(pin_left_bw, LOW);
        digitalWrite(pin_right_bw, LOW);
        digitalWrite(pin_left_fw, LOW);
        digitalWrite(pin_right_fw, LOW);
        logln("done");

        log("Initializing buzzer... ");
        pinMode(pin_buzzer, OUTPUT);
        digitalWrite(pin_buzzer, LOW);
        logln("done");
        
        log("Initializing sensors... ");
        Sensor::begin();
        logln("done");
    }

    void move(int left, int right) {
        if (left < 0) {
            digitalWrite(pin_left_fw, LOW);
            analogWrite(pin_left_bw, abs(left));
        } else if (left > 0) {
            digitalWrite(pin_left_bw, LOW);
            analogWrite(pin_left_fw, left);
        } else {
            digitalWrite(pin_left_bw, LOW);
            digitalWrite(pin_left_fw, LOW);
            return;
        }

        if (right < 0) {
            digitalWrite(pin_right_fw, LOW);
            analogWrite(pin_right_bw, abs(right));
        } else if (right > 0) {
            digitalWrite(pin_right_bw, LOW);
            analogWrite(pin_right_fw, right);
        } else {
            digitalWrite(pin_right_bw, LOW);
            digitalWrite(pin_right_fw, LOW);
            return;
        }
    }

    void buzz(unsigned int frequency, unsigned long duration) {
        tone(pin_buzzer, frequency, duration);
    }

    void buzz(unsigned int frequency) {
        buzz(frequency, 30);
    }
}
