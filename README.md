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
| D11  |                |          |             |     Buzzer      |
| D12  |                |          |             |                 |
| D13  |                |          |             |     WS2812B     |
| A0   |                |          |             | Battery Voltage |

Battery Voltage: https://docs.google.com/spreadsheets/d/1yMOeYrJNpTg3SMe8cQBoHXpgwAv61uAHFVlT2RJjNy4/edit?usp=sharing

## Instructions
Put the FTDI Chip in the robot like shown in the picture
![FTDI Orientation](https://raw.githubusercontent.com/Henning-Klatt/Robot_v4/master/images/FTDI_Orientation.JPG)

When Uploading to the robot while it is turned off, please check if the jumper is selected to 5V
![FTDI Orientation](https://raw.githubusercontent.com/Henning-Klatt/Robot_v4/master/images/Uploading_Robot_Off.JPG)

When Uploading to the robot while it is turned on (armed motors), please remove the jumper. Pay attention, the robot may drive itself from your table.
![FTDI Orientation](https://raw.githubusercontent.com/Henning-Klatt/Robot_v4/master/images/Upload_Robot_On.JPG)
