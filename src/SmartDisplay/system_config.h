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
#include "vars_global.h"
#include <EEPROM.h>
#include "hardware.h"
#include "system_eeprom.h"



byte contrast = 2;
byte autoswitch = 0;
byte speed_offset = 0;