/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 * 
 * 
 * 
 * Full Documentatition under:
 * https://wiki.fiz-o-matic.net/
 * 
 * 
 * The Sketch file is for the configuration only.
 * 
 * The setup and main functions are in the main.cpp.
 * 
 ****************************************************/

 
#define VERSION_SW "0.9.4"
#define BUILD "20240801"

/*
 * mendatory hardware defination
 */

//#define DEBUG
//#define HW_ALPHA_OLED
//#define HW_ALPHA_LCD
//#define HW_BETA
//#define HW_GAMMA



// Timezone in GMT
#define TIME_ZONE 1

/*
 * optional configuration
 */

// define key behavior 
#define KEY_DEBOUNCE 20
#define KEY_LONGPRESS 2000

// Time to disable the Display in Standby mode
// Only used for OLED Displays
#define DISPLAY_TIMEOUT 600000 // 60s

// Voltage value to turn on
#define TURN_ON_VOLTAGE 13.0

// Calibrate the Voltage 
#define VOLTAGE_CALIBRATION 1

// time between trip calculation
#define TRIP_CALC_TIMER 10000
// save trip only if distance is > x km
#define EEPROM_SAVE_TRIP1 5


// GPS Speed Offset
#define GPS_SPEED_OFFSET 0


// sitch automaticly to spped menu if engine is running
//#define DISPLAY_AUTO_SWITCH




