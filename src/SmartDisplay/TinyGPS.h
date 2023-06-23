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
#include "hardware.h"
#include "vars_global.h"


// from main.cpp
bool timer_check(unsigned long *timer, unsigned long delay);

// from trip.cpp
void calc_trip();

// local 
//void calc_trip();
float get_distance(float latitude1, float longitude1, float latitude2, float longitude2);
boolean summertime_EU(int year, byte month, byte day, byte hour, byte tzHours);
void sendUBX(uint8_t *MSG, uint8_t len);
void setupGPSpower();

static const int RXPin = GPS_RXPin, TXPin = GPS_TXPin;


int gps_satellites = 0;

/*#ifdef DEBUG
 // The serial connection to the GPS device
 #include <SoftwareSerial.h>
 SoftwareSerial ss(GPS_RXPin, GPS_TXPin);
 #define GPS_SERIAL ss
 //#define GPS_SERIAL Serial1
#else
 #define GPS_SERIAL Serial1
#endif*/
