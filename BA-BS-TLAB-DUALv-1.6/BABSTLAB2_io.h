
#define RS422TX     PIN_D3
#define RS422RX     PIN_D12

#define RS485TX     PIN_D8
#define RS485RX     PIN_A15
#define RS485EN     PIN_C14

#define RS232TX     PIN_D0
#define RS232RX     PIN_D2

// RS232 or RS485, selecatble through secondary PIC18 MCU
#define MAINTX      PIN_D5
#define MAINRX      PIN_D4
#define MAINEN      PIN_A1

// on-board LEDs
#define LED1        PIN_F3
#define LED2        PIN_F5
#define LED3        PIN_F4
#define LED4        PIN_B15

// LCD connections
#define MLCD_E      PIN_A9
#define MLCD_RS     PIN_A10
#define TLCD_E      PIN_F13
#define TLCD_RS     PIN_F12
#define LCD_CLOCK   PIN_D1
#define LCD_DATA    PIN_D11
#define LCD_LATCH   PIN_D10
#define LCD_RESET   PIN_A14

// RECEIVER1 connector
#define R1MOSI      PIN_E2
#define R1MISO      PIN_E3
#define R1CLK       PIN_G13
#define R1LD        PIN_G12
#define R1IF        PIN_E4
#define R1SP1       PIN_D7
#define R1SP2       PIN_G1
#define R1SP3       PIN_G0

// RECEIVER2 connector
#define R2MOSI      PIN_E5
#define R2MISO      PIN_G15
#define R2CLK       PIN_E6
#define R2LD        PIN_E7
#define R2IF        PIN_B4
#define R2SP1       PIN_E9
#define R2SP2       PIN_E8
#define R2SP3       PIN_A0

// SPARE1 connector - PANEL TRI-COLOR LEDs
#define RLED1       PIN_B9         // BS1 locked
#define GLED1       PIN_B10        // BS1 unlocked
#define RLED2       PIN_B13        // BS1 Signal
#define GLED2       PIN_B14        // BS1 no Signal
#define RLED3       PIN_B11        // BS2 locked
#define GLED3       PIN_B12        // BS2 unlocked
#define RLED4       PIN_B5        // BS2 Signal
#define GLED4       PIN_B8        // BS2 no Signal

// SPARE2 connector
#define SPARE_IO9   PIN_C2
#define SPARE_IO10  PIN_C1
#define SPARE_IO11  PIN_C4
#define SPARE_IO12  PIN_C3
#define SPARE_IO13  PIN_G7
#define SPARE_IO14  PIN_G6
#define SPARE_IO15  PIN_G9
#define SPARE_IO16  PIN_G8

#define BUZZER      PIN_D13

#define SMALLPIC_CLK PIN_D9
#define SMALLPIC_DAT PIN_C13

#define ANALOG_PORTS sAN0|sAN1|sAN2|sAN3

// Bit synchronizer 1 connector J2
#define  BS1_IN_SEL     PIN_D6
#define  BS1_IMPEDANCE  PIN_G14
#define  BS1_MISO       PIN_E1
#define  BS1_MOSI       PIN_E0
#define  BS1_SCK        PIN_A7
#define  BS1_CS         PIN_A6

// Bit synchronizer 2 connector J7
#define  BS2_IN_SEL     PIN_G3
#define  BS2_IMPEDANCE  PIN_G2
#define  BS2_MISO       PIN_F8
#define  BS2_MOSI       PIN_F2
#define  BS2_SCK        PIN_D15
#define  BS2_CS         PIN_D14

// randomizer control
#define  RND_RST        PIN_C1
#define  RND_MR         PIN_C3
#define  RND_GP1        PIN_G6

// 5V enable outputs
#define  SYNC1_PWR_EN   PIN_G7
#define  SYNC2_PWR_EN   PIN_G9
#define  LED_PWR_EN     PIN_C2


//=====================================================
/*
#define RS422TX     PIN_D3              // J10
#define RS422RX     PIN_D12

#define RS485TX     PIN_D8              // J13  A=1, B=2
#define RS485RX     PIN_A15
#define RS485EN     PIN_C14

#define RS232TX     PIN_D0              // J9   TX=Pin1
#define RS232RX     PIN_D2              // J9   RX=Pin3

// RS232 (J11) or RS485 (J12), selecatble through secondary PIC18 MCU
#define MAINTX      PIN_D5
#define MAINRX      PIN_D4
#define MAINEN      PIN_A1

// on-board LEDs
#define LED1        PIN_F3
#define LED2        PIN_F5
#define LED3        PIN_F4
#define LED4        PIN_B15

// LCD connections
#define MLCD_E      PIN_A9
#define MLCD_RS     PIN_A10
#define TLCD_E      PIN_F13
#define TLCD_RS     PIN_F12
#define LCD_CLOCK   PIN_D1
#define LCD_DATA    PIN_D11
#define LCD_LATCH   PIN_D10
#define LCD_RESET   PIN_A14

// RECEIVER1 connector
#define R1MOSI      PIN_E2
#define R1MISO      PIN_E3
#define R1CLK       PIN_G13
#define R1LD        PIN_G12
#define R1IF        PIN_E4
#define R1SP1       PIN_D7
#define R1SP2       PIN_G1
#define R1SP3       PIN_G0

// RECEIVER2 connector
#define R2MOSI      PIN_E5
#define R2MISO      PIN_G15
#define R2CLK       PIN_E6
#define R2LD        PIN_E7
#define R2IF        PIN_B4
#define R2SP1       PIN_E9
#define R2SP2       PIN_E8
#define R2SP3       PIN_A0

// SPARE1 connector J8 - PANEL TRI-COLOR LEDs
#define GLED1       PIN_B9         // BS1 locked
#define RLED1       PIN_B10        // BS1 unlocked
#define GLED2       PIN_B13        // BS1 Signal
#define RLED2       PIN_B14        // BS1 no Signal
#define GLED3       PIN_B11        // BS2 locked
#define RLED3       PIN_B12        // BS2 unlocked
#define GLED4       PIN_B5         // BS2 Signal
#define RLED4       PIN_B8         // BS2 no Signal

// SPARE2 connector J6
#define SPARE_IO9   PIN_C2
#define SPARE_IO10  PIN_C1
#define SPARE_IO11  PIN_C4
#define SPARE_IO12  PIN_C3
#define SPARE_IO13  PIN_G7
#define SPARE_IO14  PIN_G6
#define SPARE_IO15  PIN_G9
#define SPARE_IO16  PIN_G8

#define BUZZER      PIN_D13

#define SMALLPIC_CLK PIN_D9
#define SMALLPIC_DAT PIN_C13

#define ANALOG_PORTS sAN0|sAN1|sAN2|sAN3

// Bit synchronizer 1 connector J7
#define  RX1_SELECT  PIN_A3
#define  RX2_SELECT  PIN_A2
#define  BS1_MISO    PIN_F8
#define  BS1_MOSI    PIN_F2
#define  BS1_SCK     PIN_D15
#define  BS1_CS      PIN_D14

// Bit synchronizer 2 connector J2
#define  SPARE_IO          PIN_D6
#define  BS2_IMPEDANCE     PIN_G14
#define  BS2_MISO          PIN_E1
#define  BS2_MOSI          PIN_E0
#define  BS2_SCK           PIN_A7
#define  BS2_CS            PIN_A6

// randomizer control
#define  RND_RST        PIN_C1
#define  RND_MR         PIN_C3
#define  RND_GP1        PIN_G6

// 5V enable outputs
#define  SYNC1_PWR_EN   PIN_G7
#define  SYNC2_PWR_EN    PIN_G9
#define  LED_PWR_EN     PIN_C2

#define PLL1_DAT                  PIN_G1
#define PLL1_CLK                  PIN_D7
#define PLL1_LAT                  PIN_G0

*/