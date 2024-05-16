/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/

#include <Arduino.h>
//#include "config.h"
#include "SmartDisplay.ino"
#include "hardware.h"
//#include "can_vars.h"
//#include "vars.h"
#include "vars_global.h"
#include "OneWire.h"
#include "SmartDisplay.ino"
//#include "canbus.h"

#include <avr/wdt.h>
#include <time.h>
//#include "system_config.h"



//CAN canbus = CAN();

// from main.cpp
//void key_interrupt();
bool timer_check(unsigned long *timer, unsigned long delay);
bool millisRollover();


// from display.cpp
void display_init(void);
void display_loop();
void reset_display_pwrsave();

// from TinyGPS.cpp
void GPS_init();
void GPS_loop();

// from can...
void can_init();
void can_loop(); 

// from can_receive.cpp
//void can_receive(int packetSize);
// from can_send.cpp
//void can_send();

// from input.cpp
void input_init();
void input_loop();
void engine_state();

// from onewire.cpp
void onewire_init();
void onewire_loop();

// from key.cpp
void key_init();
void key_interrupt();
void key_loop();

// from trip.cpp
void calc_trip();
void read_eeprom_trip1();
void write_eeprom_trip1();
void clear_eeprom_trip1();

// from system_comnfig.cpp
void read_eeprom_config();
void save_eeprom_config();


/*
 * Variables ...
 */
/*volatile unsigned long last_key=0;
unsigned long key_timer = 0;

unsigned long key_pressed = 0;
unsigned long key_released = 0;*/




// Init global vars

boolean speed_available = false;
int speed = 99;
int altitude = 0;
float bord_voltage_int = 10.2;
float bord_voltage = 10.2;
boolean bord_voltage_active = true;
float batt1_voltage = 13.8;
boolean batt1_voltage_active = false;
float batt2_voltage = 12.2;
boolean batt2_voltage_active = false;


float temp_out = -127;
boolean temp_out_active = false;

int rpm = 0;
boolean rpm_active = false ;

int oil_temp = 112;
boolean oil_temp_active = false;

float oil_pressure = 2.6;
boolean oil_pressure_active = false;

int fuel_l = 48;
boolean fuel_l_active = false;

float water_temp = 86.2;
boolean water_temp_active = false;

boolean gps_available = false;
float gps_latitude = 0;
long gps_latitude_long = 0;
float gps_longitude = 0;
long gps_longitude_long = 0;
short gps_altitude = 0;

float gps_latitude_old = 0;
float gps_longitude_old = 0;

boolean summer_time = true;
int timezone = 1;
//byte timezone_gmt = 1;

int MainMenuPos = 0;
boolean engine_running = false;

// Trip Variables
unsigned long trip_timer = 0;

//float trip_distance_tmp = 0;
float trip_distance = 0;

byte hour = 0;
byte minute = 0;
byte second = 0;
byte day = 0;
byte month = 0;
byte year = 0;


