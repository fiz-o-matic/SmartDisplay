/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic Smart Cockpit configuration
 *
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/


#include <Arduino.h>
//#include "config.h"
#include "SmartDisplay.ino"
#include "hardware.h"
#include "vars_global.h"
#include "SmartDisplay.ino"
#include "canvalues.h"



#ifdef DOGS102_T25
#include <U8g2lib.h>
#include "display_u8g2_DOGS102_T25.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#endif

#ifdef SH1106_T25
#include <U8g2lib.h>
#include "display_u8g2_SH1106_T25.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#endif


#ifdef SH1107
#include <U8g2lib.h>
#include "display_u8g2_SH1107.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#endif


#define DISPLAY_PRINT(x)  u8g2.print(x)

void clear_screen();
void display_pwrsave(bool pwrsave);
void display();
void menu_logo();
void menu_clock();
void menu_speed(int DESC, float VALUE, byte DIGITS, String SUFFIX);
void menu_values(int DESC, float VALUE, byte DIGITS, String SUFFIX);
void menu_2values(int DESC, long VALUE1, byte DIGITS1, String SUFFIX1, long VALUE2, byte DIGITS2, String SUFFIX2);
void menu_values(char DESC[18], char VALUE[9], char SUFFIX[5]);
void menu_2values(char DESC[18], char VALUE1[9], char SUFFIX1[5], char VALUE2[9], char SUFFIX2[5]);
void menu_gps_1();
void menu_can();
void menu_info();
void menu_config(int DESC, byte VALUE);
void menu_config_bool(int DESC, byte VALUE);

void print_string(int string_id);


// from main.cpp
bool timer_check(unsigned long *timer, unsigned long delay);

// from canbus.cpp
bool can_next();


// from TinyGPS

uint16_t tinyGPS_watchdog_reset_in();


unsigned long display_timer = 0;
unsigned long display_timeout = 0;
boolean display_active = true;
boolean display_block = false;
boolean display_menu_set = false;

int OldPos = 0;


// Strings

#define STR_SPEED 1
#define STR_SPEED_S "Geschwindigkeit"
#define STR_WATER_TEMP 2
#define STR_WATER_TEMP_S "Wassertemperatur"
#define STR_FUEL 3
#define STR_FUEL_S "Tankinhalt"
#define STR_OIL_TEMP 4
#define STR_OIL_TEMP_S "\xd6ltempteratur"
#define STR_OIL_PRESSURE 5
#define STR_OIL_PRESSURE_S "\xd6ldruck"
#define STR_BORD_VOLT 6
#define STR_BORD_VOLT_S "Bordspannung"
#define STR_BATT1 7
#define STR_BATT1_S "Batterie 1"
#define STR_BATT2 8
#define STR_BATT2_S "Batterie 2"
#define STR_RPM 9
#define STR_RPM_S "RPM"

#define STR_NOGPS 10
#define STR_NOGPS_S "keine GPS Daten..."
#define STR_ALTITUTE 11
#define STR_ALTITUTE_S "Höhe"
#define STR_LAT 12
#define STR_LAT_S "Latitude"
#define STR_LONG 13
#define STR_LONG_S "Longitude"
#define STR_SATELITES 14
#define STR_SATELITES_S "Satelites"
#define STR_TEMP 15
#define STR_TEMP_S "Temperatur"
#define STR_OUT 16
#define STR_OUT_S "Aussen"
#define STR_IN 17
#define STR_IN_S "Innen"
#define STR_HUMIDITY 18
#define STR_HUMIDITY_S "Luftfeuchtigkeit"
#define STR_COORDINATES 19
#define STR_COORDINATES_S "GPS Koordinaten"
#define STR_TRIP 20
#define STR_TRIP_S "Trip"
#define STR_BORD_VOLT_INT 21
#define STR_BORD_VOLT_INT_S "Bordspannung (KI)"
#define STR_CONTRAST 22
#define STR_CONTRAST_S "Kontrast"
#define STR_AUTOSWITCH 23
#define STR_AUTOSWITCH_S "Auto Switch"
#define STR_SPEEDOFFSET 24
#define STR_SPEEDOFFSET_S "Speed Offset"

#define STR_KMH 101
#define STR_KMH_S "k/mh"
#define STR_CELCIUS 102
#define STR_CELCIUS_S "\xb0 C"
#define STR_BAR 103
#define STR_BAR_S "bar"
#define STR_V 104
#define STR_V_S "V"
#define STR_L 105
#define STR_L_S "l"
#define STR_RPM_SIGN 106
#define STR_RPM_SIGN_S "U/min"
#define STR_M 107
#define STR_M_S "m"


#define ERROR 0
#define INFO_MSG 1
#define DEBUG_MSG 2
#define NOTIFY 3
#define SERIAL_MSG 4
#define STORAGE 5
#define ALARM 6
#define DEBUG_IO 7
#define GPS 8
#define TINYGSM_MSG 9
#define BLYNK_MSG 10
#define TRACE_MSG 11
#define U8G2_MSG 12
#define I2C_MSG 13
#define BOOTMSG 14
#define CAN_MSG 15