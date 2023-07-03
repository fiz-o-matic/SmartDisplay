/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay configuration
 *
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/


/*
 * mendatory hardware defination
 */

//#define DEBUG // this disables GPS on the Serial Port
//#define HW_ALPHA_OLED
//#define HW_ALPHA_LCD

#define VERSION_SW "0.8.1"

// Timezone in GMT
#define TIME_ZONE 1

/*
 * optional configuration
 */

// Time to disable the Display in Standby mode
#define DISPLAY_TIMEOUT 600000 // 60s

// Voltage value to turn on
#define TURN_ON_VOLTAGE 13.2

// Calibrate the Voltage 
#define VOLTAGE_CALIBRATION 1

// time between trip calculation
#define TRIP_CALC_TIMER 10000

// GPS Speed Offset
#define GSP_SPEED_OFFSER 5


// sitch automaticly to spped menu if engine is running
#define DISPLAY_AUTO_SWITCH


// EEPROM lifetime is 100,000 write cycles.
// With 16 values in EEPROM and write every km max. 
// EEPROM Lifetime is 1,600,000 km

// number of values in eeprom
#define EEPROM_VAL_TRIP1 16

// save trip only if distance is > x km
#define EEPROM_SAVE_TRIP1 1