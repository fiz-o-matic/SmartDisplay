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
  if ( !engine_running ) return;

  trip_distance_tmp = get_distance(gps_latitude, gps_longitude, gps_latitude_old, gps_longitude_old);
  trip_distance += trip_distance_tmp / 1000;
  gps_latitude_old = gps_latitude;
  gps_longitude_old = gps_longitude;

  //trip_time_tmp = unixTime(hour, minute, second, year, month, day);
  //trip_time += trip_time_tmp - trip_time_old;

}

void reset_trip() {
    trip_distance = 0;
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