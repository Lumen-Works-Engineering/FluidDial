Compiled bin files is all that PiBot provides for their cnc pendant with fluiddial. No source code.
The file LGFX_AutoDetect_ESP32_all.hpp was obtained from the PiBot CNC Pendant developer. He stated he's not much of a developer and doesn't know how to use git.  He said this was the file he changed the most for fluiddial to work with the pibot cnc pendant.
These are the changes he said he made.
in line 3102-3116
          {
            auto t = new lgfx::Touch_FT5x06();
            auto cfg = t->config();
            cfg.pin_int  = GPIO_NUM_36;
            cfg.pin_sda  = GPIO_NUM_32;
            cfg.pin_scl  = GPIO_NUM_25;
            cfg.i2c_port = I2C_NUM_1;
            cfg.x_min = 239;
            cfg.x_max = 0;
            cfg.y_min = 319;
            cfg.y_max = 0;
            cfg.bus_shared = false;
            t->config(cfg);
            p->touch(t);
          }

in line 3148
            cfg.invert = true;

He also stated:
Additionally, I also modified the button sequence in src\Hardware2432.cpp
            /////addddd
            red_button_pin   = GPIO_NUM_4;   // RGB LED Red
            dial_button_pin  = GPIO_NUM_16;  // RGB LED Blue
            green_button_pin = GPIO_NUM_17;  // RGB LED Green
            pinMode(red_button_pin, INPUT_PULLUP);
            pinMode(dial_button_pin, INPUT_PULLUP);
            pinMode(green_button_pin, INPUT_PULLUP);
            //////////adddd

2025-11-25 14:50 Pibot dev posted this in discord:

1. Using the ILI9341 LCD screen display driver,

// Define ILI9341 pins  
#define TFT_CS 15 // Chip select pin  
#define TFT_DC 2 // Data/command selection pin  
#define TFT_MOSI 13 // MOSI (SDI) pin  
#define TFT_CLK 14 // SCK pin  
#define TFT_MISO 12 // MISO (SDO) pin  
#define TFT_RST -1 // Reset pin (using the ESP32's EN pin, no operation required in code)  
#define TFT_LED 21 // Backlight control pin  

2. The touch driver uses FT6336U, with SDA connected to IO32, SCL to IO25, IRQ to IO36, and CS to IO33.

// Define FT6336U pins  
#define TOUCH_SDA 32 // SDA pin  
#define TOUCH_SCL 25 // SCL pin  
#define TOUCH_IRQ 36 // Interrupt pin  
#define TOUCH_CS 33 // Chip select pin (not used)  

3. The IO26 pin is connected to the center point of a 10k variable resistor, with the top connected to 3.3V and the bottom to GND.

4. TF circuit: MISO connected to IO19, CS to IO5, MOSI to IO23, CLK to IO18.

5. IO4, IO16, and IO17 are connected to three buttons, which are grounded when pressed (no pull-up resistors).

6. IO22 and IO27 are connected to the A and B of an encoder (no pull-up resistors).

7. IO34, IO35, and IO39 have 10k pull-up resistors, and these three pins are connected to a three-position switch.