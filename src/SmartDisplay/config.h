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


/*
 * optional configuration
 */

// Time to disable the Display in Standby mode
#define DISPLAY_TIMEOUT 600000 // 60s

// Voltage value to turn on
#define TURN_ON_VOLTAGE 13.5

// Calibrate the Voltage 
#define VOLTAGE_CALIBRATION 0.9