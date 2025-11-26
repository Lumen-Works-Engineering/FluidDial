## PiBot Pendant ESP32-WROOM-32-NB Pinout Table

| Pin | ESP32 Name | Signal Name   | Connects To                     |
| --- | ---------- | ------------- | ------------------------------- |
| 1   | GND        | GND           | Ground                          |
| 2   | VDD33      | VDD33         | +3.3V Power                     |
| 3   | EN         | MCU_RST       | Enable / Reset                  |
| 4   | SENSOR_VP  | TP_IRQ (io36) | FT6336U Touch IRQ               |
| 5   | SENSOR_VN  | IO_39         | Band Switch input               |
| 6   | IO34       | IO_34         | Band Switch input               |
| 7   | IO35       | IO_35         | Band Switch input               |
| 8   | IO32       | TP_SDA        | FT6336U Touch I2C SDA           |
| 9   | IO33       | ADC_33        | Potentiometer (MID_POT via R53) |
| 10  | IO25       | TP_SCL        | FT6336U Touch I2C SCL           |
| 11  | IO26       | BEEP_IO26     | Buzzer / Beeper                 |
| 12  | IO27       | ENC_B_IO27    | CNC Wheel Encoder B             |
| 13  | IO14       | LCD_SCK       | ILI9341 LCD SPI Clock           |
| 14  | IO12       | LCD_SDO       | ILI9341 LCD SPI MISO            |
| 15  | GND        | GND           | Ground                          |
| 16  | IO13       | LCD_SDI       | ILI9341 LCD SPI MOSI            |
| 17  | SD2        | —             | (Unused)                        |
| 18  | SD3        | —             | (Unused)                        |
| 19  | CMD        | —             | (Unused)                        |
| 20  | CLK        | —             | (Unused)                        |
| 21  | SD0        | —             | (Unused)                        |
| 22  | SD1        | —             | (Unused)                        |
| 23  | IO15       | LCD_CS        | ILI9341 LCD Chip Select         |
| 24  | IO2        | LCD_DC        | ILI9341 LCD Data/Command        |
| 25  | IO0        | IO_0          | Boot / Band Switch              |
| 26  | IO4        | KEY_IO4       | Button 1                        |
| 27  | IO16       | KEY_IO16      | Button 2                        |
| 28  | IO17       | KEY_IO17      | Button 3                        |
| 29  | IO5        | TF_CS         | SD Card Chip Select             |
| 30  | IO18       | TF_CLK        | SD Card SPI Clock               |
| 31  | IO19       | MCU_MISO      | SD Card SPI MISO                |
| 32  | NC         | NC            | Not Connected                   |
| 33  | IO21       | LCD_IO21      | ILI9341 LCD Reset               |
| 34  | RXD0       | MCU_RXD       | UART RX (CH340 USB & RJ12/PH55) |
| 35  | TXD0       | MCU_TXD       | UART TX (CH340 USB & RJ12/PH55) |
| 36  | IO22       | ENC_A_IO22    | CNC Wheel Encoder A             |
| 37  | IO23       | MCU_MOSI      | SD Card SPI MOSI                |
| 38  | GND        | GND           | Ground                          |
| 39  | GND        | GND           | Ground                          |
