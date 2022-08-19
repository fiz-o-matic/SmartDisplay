/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay
 *
 *  Definations of Variables which are used.
 *  All Variables are defined in this file.
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/


/*
 * Variables ...
 */















// TIME
//#define CAN_gps_SLAVE
boolean summer_time = true;
int timezone = 1;
byte timezone_gmt = 1;

#ifndef CAN_time_SLAVE

#endif





boolean gps_fixstatus;
int gps_fixerrcnt = 0;
int gps_year;
int gps_day;
int gps_month;
int gps_hour;
int gps_minute;
int gps_second;
//float gps_speed;
//uint8_t gps_speed_max = 0;
//uint8_t gps_speed_max_trip = 0;
//uint8_t gps_speed_avg = 0;
//uint8_t gps_speed_avg_trip = 0;
uint16_t gps_course;
//float gps_altitude;
//int gps_view_satellites;
int gps_satellites;
//float gps_altitude_blynk;
//int gps_view_satellites_blynk = 255;
//int gps_used_satellites_blynk = 255;
//float gps_latitude, gps_longitude;
/*float gps_latitude_old = 0;
float gps_longitude_old = 0;
float gps_latitude_lastlog = 0;
float gps_longitude_lastlog = 0;
float gps_latitude_blynk = 0;
float gps_longitude_blynk = 0;
float gps_latitude_geo_fence = 0;
float gps_longitude_geo_fence = 0;*/
//boolean gps_fix = false;
//uint32_t gps_distance = 0;
//float accuracy = 0;




// a smal buffer
//char buf[64]; //
int buffpos = 0;
//int i_tmp = 0;
char inChar;



unsigned long gps_timer = 0;


//boolean debug = true;
//String msg;


// Trip Variables
/**
unsigned long trip_timer = 0;

float trip_distance_tmp = 0;
unsigned long trip_time = 0;
unsigned long trip_time_tmp = 0;
unsigned long trip_time_old = 0;
**/




/*
 * converting a normal time into unix time
 * based on http://christianscode.blogspot.de/2015/07/arduino-timestamp-function.html
 *
 * Function extracted from the library http://playground.arduino.cc/Code/Time
 * if you just need the function without compiling few kbs and you need to save
 * space, this is the way to go
 *
 */

#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24UL)

// leap year calulator expects year argument as years offset from 1970
#define LEAP_YEAR(Y)     ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )
static  const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0
