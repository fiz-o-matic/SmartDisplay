/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/
// https://ukhas.org.uk/guides:ublox_psm
// https://content.u-blox.com/sites/default/files/products/documents/u-blox6-GPS-GLONASS-QZSS-V14_ReceiverDescrProtSpec_%28GPS.G6-SW-12013%29_Public.pdf
#include "TinyGPS.h"


#ifdef GPS_ENABLED

#include <TinyGPS++.h>

// The TinyGPS++ object
TinyGPSPlus gps;

void tinyGPS_init() {
  GPS_SERIAL.begin(GPS_BAUD);

  //setupGPSpower();
}


void tinyGPS_loop() {
  unsigned long start = millis();
  do
  {
    while (GPS_SERIAL.available())
      gps.encode(GPS_SERIAL.read());
      //DEBUG_PRINT(GPS_SERIAL.read());
      //DEBUG_PRINT(F("."));
  } while (millis() - start < 500);

  DEBUG_PRINT(F("chars processed: "));
  DEBUG_PRINTLN(gps.charsProcessed());

  if ( gps.charsProcessed() >= 1000 ) {
    gps_available = true;
  }
  else {
    gps_available = false;
  }

  DEBUG_PRINT(F("Satelites: "));
  DEBUG_PRINTLN(gps.satellites.value());
  
  if ( gps.speed.isValid() ) {
    speed_available = true;
    speed = gps.speed.kmph() + GSP_SPEED_OFFSER;
  }
  else {
    speed = 0;
    speed_available = false;
  }

  if ( gps.satellites.isValid() ) {
    gps_satellites = gps.satellites.value();
  }

  if ( gps.location.isValid() ) {
    gps_latitude = gps.location.lat();
    gps_longitude = gps.location.lng();
    gps_altitude = gps.altitude.meters();

    // set the trip calculator
    calc_trip();
  }


  if (gps.time.isValid())
  {
    year = gps.date.year();
    month = gps.date.month();
    day = gps.date.day();

    hour = gps.time.hour() + TIME_ZONE;
    if ( hour >= 24 ) {
      hour = hour - 24;
      day = day + 1;
    }
    minute = gps.time.minute();
    second = gps.time.second();
    
    DEBUG_PRINT(F("GPS Time: "));
    DEBUG_PRINT(hour);
    DEBUG_PRINT(F(":"));
    DEBUG_PRINT(minute);
    DEBUG_PRINT(F(":"));
    DEBUG_PRINTLN(second);

    if ( summertime_EU(year, month, day, hour, TIME_ZONE) ) {
      hour++;
    }

  }
}







/*
   Summer time Yes or No
*/
boolean summertime_EU(int year, byte month, byte day, byte hour, byte tzHours)
// European Daylight Savings Time calculation by "jurs" for German Arduino Forum
// input parameters: "normal time" for year, month, day, hour and tzHours (0=UTC, 1=MEZ)
// return value: returns true during Daylight Saving Time, false otherwise
{
  if (month < 3 || month > 10) return false; // keine Sommerzeit in Jan, Feb, Nov, Dez
  if (month > 3 && month < 10) return true; // Sommerzeit in Apr, Mai, Jun, Jul, Aug, Sep
  //if ( (month == 3) && ( (hour + 24 * day) >= (1 + tzHours + 24 * (31 - (5 * year / 4 + 4) % 7)) ) || ( month == 10 && (hour + 24 * day) < (1 + tzHours + 24 * (31 - (5 * year / 4 + 1) % 7)))) {
  if (((month==3) && ((hour + 24 * day)>=(1 + tzHours + 24*(31 - (5 * year /4 + 4) % 7)))) || ((month==10) && ((hour + 24 * day)<(1 + tzHours + 24*(31 - (5 * year /4 + 1) % 7))))) {
    return true;
  }
  else {
    return false;
  }
}


/*unsigned long unixTime(int hr, int min, int sec, int dy, int mnth, int yr) {
  // assemble time elements into time_t
  // note year argument is offset from 1970 (see macros in time.h to convert to other formats)
  // previous version used full four digit year (or digits since 2000),i.e. 2009 was 2009 or 9

  // year can be given as full four digit year or two digts (2010 or 10 for 2010);
  //it is converted to years since 1970
  if ( yr > 99)
    yr = yr - 1970;
  else
    yr += 30;

  int i;
  uint32_t seconds;

  // seconds from 1970 till 1 jan 00:00:00 of the given year
  seconds = yr * (SECS_PER_DAY * 365);
  for (i = 0; i < yr; i++) {
    if (LEAP_YEAR(i)) {
      seconds +=  SECS_PER_DAY;   // add extra days for leap years
    }
  }

  // add days for this year, months start from 1
  for (i = 1; i < mnth; i++) {
    if ( (i == 2) && LEAP_YEAR(yr)) {
      seconds += SECS_PER_DAY * 29;
    } else {
      seconds += SECS_PER_DAY * monthDays[i - 1]; //monthDay array starts from 0
    }
  }
  seconds += (dy - 1) * SECS_PER_DAY;
  seconds += hr * SECS_PER_HOUR;
  seconds += min * SECS_PER_MIN;
  seconds += sec;
  //TRACE_PRINT(F("#UnixTime: "));
  //TRACE_PRINTLN(seconds);
  return (long)seconds;
}*/

// Send a byte array of UBX protocol to the GPS
void sendUBX(uint8_t *MSG, uint8_t len) {
  for(int i=0; i<len; i++) {
    GPS_SERIAL.write(MSG[i]);
  }
  //Serial.println();
}
 
void setupGPSpower() {
  //Set GPS ot Power Save Mode
  uint8_t setPSM[] = { 0xB5, 0x62, 0x06, 0x11, 0x02, 0x00, 0x08, 0x01, 0x22, 0x92 }; // Setup for Power Save Mode (Default Cyclic 1s)

  //Set GPS ot Max Performance Mode (default)
  //uint8_t setPSM[] = { 0xB5, 0x62, 0x06, 0x11, 0x02, 0x00, 0x08, 0x00, 0x21, 0x91 };

  sendUBX(setPSM, sizeof(setPSM)/sizeof(uint8_t));
  DEBUG_PRINTLN(F("Set GPS in Power Safe Mode"));

  uint8_t setUPDATE[] = { 0xB5, 0x62, 0x06, 0x3B, 0x2C, 0x00, 0x01, 0x06, 0x00, 0x00, 0x00, 0x90, 0x03, 0x00, 0x10, 0x27, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x4F, 0xC1, 0x03, 0x00, 0x87, 0x02, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x64, 0x40, 0x01, 0x00, 0xE4, 0x8B }; // Setup for Power Save Mode (Default Cyclic 1s)
  sendUBX(setUPDATE, sizeof(setUPDATE)/sizeof(uint8_t));

  uint8_t GPSoff[] = {0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x4D, 0x3B };
  //sendUBX(GPSoff, sizeof(GPSoff)/sizeof(uint8_t));
  DEBUG_PRINTLN(F("GPS OFF"));
  
  //delay(30000);
 
  //Restart GPS
  uint8_t GPSon[] = {0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x4C, 0x37 };
  //sendUBX(GPSon, sizeof(GPSon)/sizeof(uint8_t));
  DEBUG_PRINTLN(F("GPS ON"));
  
}

#else


void tinyGPS_init() {}
void tinyGPS_loop() {}

#endif
