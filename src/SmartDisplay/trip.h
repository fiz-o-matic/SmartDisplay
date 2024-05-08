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
#include "config.h"
#include "vars_global.h"
#include <EEPROM.h>
#include "hardware.h"
#include "system_eeprom.h"


float trip_distance_tmp = 0;
float f = 0.00f;
float tmp = 0.00f;

// from main.cpp
bool timer_check(unsigned long *timer, unsigned long delay);

// local 
float get_distance(float latitude1, float longitude1, float latitude2, float longitude2);
void read_eeprom_trip1();
void write_eeprom_trip1();
void clear_eeprom_trip1();
