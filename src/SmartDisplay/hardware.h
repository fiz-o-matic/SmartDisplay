/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay Hardware configuration
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/
#include <Arduino.h>
//#include "config.h"
#include "SmartDisplay.ino"


//global definition
//#define KEY 3


// ONLY for debugging
#define GPS_RXPin A0
#define GPS_TXPin A1


#define GPS_WATCHDOG_TIMOUT_S 60



// analog Input
//#define IN1 A3
//#define IN1_MULTIPLICATOR 0.015234


/*
 * GAMMA Version with DOGS102 LCD and CAN Bus
 */
#ifdef HW_GAMMA

#define VERSION_HW "GAMMA w/ DOGS102"

#define KEY PIN_A5

// analog Input
#define IN1 A4
// Volatege multiplication
//#define A3_MULTIPLICATOR 0.02273438
#define VOLTAGE_RANGE_MV 19400

#define GPS_ENABLED
#define GPS_BAUD 9600
#define GPS_SERIAL Serial1
#define GPS_RESET_PIN 11

// OneWire Bus
#define ONEWIRE
//#define ONE_WIRE_BUS PIN_A6
#define OW_PIN 18


#define CANBUS
#define CAN_IRQ 10
#define CAN_CS 7


#define DOGS102_T25
#define U8G2_DISPLAY
//#define ENABLE_DISPLAY


#define DISPLAY_CS 24
#define DISPLAY_RST 23
#define DISPLAY_DC 22

//Menu and Feature defination
#define MENU_clock 1
#define MENU_speed 2
#define MENU_bord_voltage_int 3
#define MENU_trip 4
#define MENU_altitude 5
#define MENU_CAN 6
#define MENU_CAN_NEXT 7
#define MENU_gps 8
#define MENU_Info 9

#endif



/*
 * BETA Version with DOGS102 LCD
 */
#ifdef HW_BETA

#define VERSION_HW "BETA w/ DOGS102"

#define KEY PIN_A5

// analog Input
#define IN1 A4
// Volatege multiplication
//#define A3_MULTIPLICATOR 0.02273438
#define VOLTAGE_RANGE_MV 19400

#define GPS_ENABLED
#define GPS_BAUD 9600
#define GPS_SERIAL Serial1
#define GPS_RESET_PIN 11

// OneWire Bus
#define ONEWIRE
//#define ONE_WIRE_BUS PIN_A6
#define OW_PIN 18

/*
#define CANBUS
#define CAN_IRQ 10
#define CAN_CS 7
*/

#define DOGS102_T25
#define U8G2_DISPLAY
//#define ENABLE_DISPLAY


#define DISPLAY_CS 24
#define DISPLAY_RST 23
#define DISPLAY_DC 22

//Menu and Feature defination
#define MENU_clock 1
#define MENU_speed 2
#define MENU_bord_voltage_int 3
#define MENU_trip 4
#define MENU_altitude 5
//#define MENU_CAN 2
//#define MENU_CAN_NEXT 3
#define MENU_gps 6
#define MENU_Info 7

#endif



/*
 * ALPHA Version with SH1107 OLED
 */
#ifdef HW_ALPHA_OLED

#define VERSION_HW "ALPHA with OLED"

#define KEY 3

// analog Input
#define IN1 A3
#define IN1_MULTIPLICATOR 0.015234
// Volatege multiplication
#define VOLTAGE_RANGE_MV 13950


#define GPS_ENABLED
#define GPS_BAUD 9600
#define GPS_RXPin A0
#define GPS_TXPin A1
#define GPS_SERIAL Serial

// Volatege multiplication
#define A3_MULTIPLICATOR 0.02273438

// OneWire Bus
#define ONEWIRE
#define ONE_WIRE_BUS 5

#define SH1107
#define U8G2_DISPLAY
//#define ENABLE_DISPLAY
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif


#define DISPLAY_CS 6
#define DISPLAY_DC 7
#define DISPLAY_RST 8

//Menu and Feature defination
#define MENU_clock 1
#define MENU_speed 2
#define MENU_bord_voltage 3
#define MENU_altitude 4
#define MENU_gps 5
#define MENU_trip 6

#endif

/*
 * ALPHA Version with DOGS102 LCD
 */
#ifdef HW_ALPHA_LCD

#define VERSION_HW "ALPHA with LCD"

#define KEY 3

// analog Input
#define IN1 A3
#define IN1_MULTIPLICATOR 0.015234
// Volatege multiplication
#define VOLTAGE_RANGE_MV 13950


#define GPS_ENABLED
#define GPS_BAUD 9600
#define GPS_SERIAL Serial

// OneWire Bus
#define ONEWIRE
#define ONE_WIRE_BUS 5

// Volatege multiplication
#define A3_MULTIPLICATOR 0.02273438

#define DOGS102_T25
#define U8G2_DISPLAY
//#define ENABLE_DISPLAY


#define DISPLAY_CS 8
#define DISPLAY_DC 6
#define DISPLAY_RST 7

//Menu and Feature defination
#define MENU_clock 1
#define MENU_speed 2
#define MENU_bord_voltage_int 3
#define MENU_altitude 4
#define MENU_gps 5
#define MENU_trip 6

#endif

/*
 * CAN Version
 * 
 */
#ifdef SW_CAN
#define CANBUS
#define ONEWIRE


//Menu and Feature defination
//#define CAN_time_SLAVE
#define MENU_clock 1
#define MENU_speed 2

//#define CAN_fuel_water_SLAVE
#define MENU_temp 3
#define MENU_fuel 4

//#define CAN_oil_SLAVE
//#define MENU_oil_temp 5
//#define MENU_oil_pressure 6
//#define CAN_voltage_SLAVE
//#define MENU_batt1_voltage 7
//#define MENU_batt2_voltage 8
//#define MENU_bord_voltage 9
//#define MENU_bord_voltage_int 10
//#define CAN_rpm_SLAVE
//#define MENU_rpm 11
//#define CAN_gps_SLAVE
//#define MENU_gps 12
//#define MENU_altitude 13
//#define CAN_klima_SLAVE
//#define MENU_temp_hum_out 14
//#define MENU_temp_hum_in 15
//#define CAN_trip_SLAVE
//#define MENU_trip_today 16
//#define MENU_trip_long 17
//#define MENU_trip_all 18

//#define CAN_display_MASTER

#endif //SW_CAN



#ifdef SW_GPS
#define GPS_ENABLED
#define ONEWIRE


//Menu and Feature defination
#define MENU_clock 1
#define MENU_speed 2
#define MENU_bord_voltage_int 3
#define MENU_trip 4
//#define MENU_altitude 4
//#define MENU_gps 5

// CAN is disabled in Debugging Mode
//#ifndef DEBUG
#define CANBUS
#define CAN_fuel_water_SLAVE
#define MENU_temp 6
#define MENU_fuel 7

#define CAN_oil_SLAVE
#define MENU_oil_temp 8
#define MENU_oil_pressure 9

#define CAN_rpm_SLAVE
#define MENU_rpm 10
//#endif



#endif //SW_GPS

#ifdef SW_GPS_ONLY
#define GPS_ENABLED
#define ONEWIRE


//Menu and Feature defination
#define MENU_clock 1
#define MENU_speed 2
#define MENU_bord_voltage 3
#define MENU_altitude 4
#define MENU_gps 5
#define MENU_trip 6


#endif //SW_GPS_ONLY

#ifdef SH1106_T25
#define U8G2_DISPLAY
//#define ENABLE_DISPLAY
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#define DISPLAY_CS 8
#define DISPLAY_DC 7
#define DISPLAY_RST 6
//#include "display_u8g2_SH1106_T25.h"

#endif

#ifdef SH1107M4808
#define U8G2_DISPLAY
//#define ENABLE_DISPLAY
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#define DISPLAY_CS 22
#define DISPLAY_DC 23
#define DISPLAY_RST 24
#endif


#ifdef SH1107M32
#define U8G2_DISPLAY
//#define ENABLE_DISPLAY
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#define DISPLAY_CS 6
#define DISPLAY_DC 7
#define DISPLAY_RST 8
//U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ DISPLAY_CS, /* dc=*/ DISPLAY_DC, /* reset=*/ DISPLAY_RST);
//#include "display_u8g2_SH1106.h"
//#include "display_u8g2_SH1107.h"
#endif


/*#ifdef DOGS102_T25
#define U8G2_DISPLAY
#define ENABLE_DISPLAY
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#define DISPLAY_CS 8
#define DISPLAY_DC 6
#define DISPLAY_RST 7
//#include "display_u8g2_DOGS102_T25.h"
#endif*/






/*#ifdef DEBUG
 #define DEBUG_PRINT(x)  Serial.print (x)
 #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
#endif*/

#if defined(DEBUG)
    #define DEBUG_PRINT(...)  { Serial.print("[" + String(millis()) + "]"); Serial.println(__VA_ARGS__); }
    //#define DEBUG_PRINT(...)  BLYNK_LOG1(__VA_ARGS__)
    #define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
    #define DEBUG_PRINTLN(...)
#endif

