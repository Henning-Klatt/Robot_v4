# Pinout
| 328P | Motor Driver   | Buttons  | LED's       |  Miscellaneous  |
|------|----------------|----------|-------------|-----------------|
| D2   |                |          |             | i2c Multiplexer |
| D3   | Right forward  |          |             |                 |
| D4   |                |  CALIB   |             |                 |
| D5   |                |          |             |   i2c Sensor 5  |
| D6   | Right backward |          |             |                 |
| D7   |                |          | Status LED  |                 |
| D8   |                |          |             |                 |
| D9   | Left backward  |          |             |                 |
| D10  | Left forward   |          |             |                 |
| D11  |                |          |             | Buzzer, WS2812B |
| A0   |                |          |             | Battery Voltage |

Battery Voltage: https://docs.google.com/spreadsheets/d/1yMOeYrJNpTg3SMe8cQBoHXpgwAv61uAHFVlT2RJjNy4/edit?usp=sharing

The WS2812B LED's do affect the Buzzer, a silent brumming is hearable. Hopefully no one will notice this while the motors are running.

ToDo: Put the WS2812B LED's to Pin D8 in order to stop the Buzzer going crazy.
