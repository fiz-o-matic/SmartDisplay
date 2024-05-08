/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/


#include "trip.h"


void calc_trip() {
  if ( !timer_check(&trip_timer, TRIP_CALC_TIMER) ) return;
  
  // write eeprom even if engine is off
  write_eeprom_trip1();
  
  if ( !engine_running ) return;

  

  if ( gps_latitude_old != 0 ) {
    trip_distance_tmp = get_distance(gps_latitude, gps_longitude, gps_latitude_old, gps_longitude_old);
    trip_distance += trip_distance_tmp / 1000;
    gps_latitude_old = gps_latitude;
    gps_longitude_old = gps_longitude;

    //write_eeprom_trip1();
  }
  else {
    gps_latitude_old = gps_latitude;
    gps_longitude_old = gps_longitude;
  }

  //trip_time_tmp = unixTime(hour, minute, second, year, month, day);
  //trip_time += trip_time_tmp - trip_time_old;

}

void reset_trip() {
    trip_distance = 0;
    clear_eeprom_trip1();
}

/*
 *    caclulating distance
 */
float get_distance(float latitude1, float longitude1, float latitude2, float longitude2) {
  float delLat = (latitude2 - latitude1) * 111194.9;
  float delLong = 111194.9 * (longitude2 - longitude1) * cos(radians((latitude2 + latitude1) / 2));
  float distance = sqrt(pow(delLat, 2) + pow(delLong, 2));

  return distance;
}

void read_eeprom_trip1() {
  //float dist = 0.00f;
  //float f = 0.00f;
  //float tmp = 0.00f;
  byte tmp_i = 0;

  for (byte i=0;i<=EEPROM_VAL_TRIP1;i++) {
    EEPROM.get( i*4, f );
    //DEBUG_PRINT(i*4);
    //DEBUG_PRINT(F(": "));
    //DEBUG_PRINT(f);
    if ( f > tmp ) {
      tmp = f;
      tmp_i = i;
      trip_distance = f;
    }
  }
  //DEBUG_PRINT(tmp_i*4);
  //DEBUG_PRINT(F(": "));
  //DEBUG_PRINT(tmp);
  DEBUG_PRINT("TRIP: " + String(tmp_i*4) + " : " + String(trip_distance));
  //DEBUG_PRINT(tmp_i*4);
  //DEBUG_PRINT(F(": "));
  //DEBUG_PRINT(trip_distance);
  
}

void write_eeprom_trip1() {
  /*EEPROM.put(0, 12345.245);
  EEPROM.put(4, 66345.4578);
  EEPROM.put(8, 547345.784);
  EEPROM.put(12, 4574.367);*/
  //float f = 0.00f;
  //float tmp = 0.00f;
  int tmp_i = 0;
  f = 0;
  tmp = 0;

  for (byte i=0;i<=EEPROM_VAL_TRIP1;i++) {
    EEPROM.get( i*4, f );
    /*DEBUG_PRINT(i*4);
    DEBUG_PRINT(F(": "));
    DEBUG_PRINT(f);*/
    if ( f > tmp ) {
      tmp = f;
      tmp_i = i;
      //DEBUG_PRINT("*");
    }
  }
  /*DEBUG_PRINT("LAST ");
  DEBUG_PRINT(tmp_i*4);
  DEBUG_PRINT(F(": "));
  DEBUG_PRINT(tmp);*/

  if ( tmp_i == EEPROM_VAL_TRIP1) {
    tmp_i=0;
  }
  else {
    tmp_i++;
  }

  //randomSeed(analogRead(A4));
  //byte rndnum = random(0,EEPROM_VAL_TRIP1);
  /*while ( rndnum == tmp_i ) {
    DEBUG_PRINT("new rndnum...");
    //DEBUG_PRINT(rndnum);
    //DEBUG_PRINT(tmp_i);
    rndnum = random(0,EEPROM_VAL_TRIP1);
  }*/

  DEBUG_PRINT(F(" TRIP: "));
  DEBUG_PRINT(trip_distance);
  if ( tmp + EEPROM_SAVE_TRIP1 <= trip_distance  ) {
    /*DEBUG_PRINT(F("WRITE: "));
    DEBUG_PRINT(tmp_i*4);
    DEBUG_PRINT(F(" : "));
    DEBUG_PRINT(trip_distance);*/
    EEPROM.put(tmp_i*4, trip_distance);
  }
  /*else {
    DEBUG_PRINT("NO NEED to write EEPROM");
    //DEBUG_PRINT(F(" TRIP: "));
    //DEBUG_PRINT(trip_distance);
    trip_distance += float(rndnum)*8/10;
  }*/
  
}

void clear_eeprom_trip1() {
  for (byte i=0;i<=EEPROM_VAL_TRIP1;i++) {
    EEPROM.put(i*4, 0.00);
    DEBUG_PRINT(F("clear: "));
    DEBUG_PRINT(i*4);
  }
}