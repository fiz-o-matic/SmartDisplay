/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/

extern int MainMenuPos;
extern boolean engine_running;

extern float bord_voltage_int;
extern float bord_voltage;
extern boolean bord_voltage_active;

extern float batt1_voltage;
extern boolean batt1_voltage_active;

extern float batt2_voltage;
extern boolean batt2_voltage_active;

extern float temp_out;
extern boolean temp_out_active;

extern int rpm;
extern boolean rpm_active;

extern int oil_temp;
extern boolean oil_temp_active;

extern float oil_pressure;
extern boolean oil_pressure_active;

extern int fuel_l;
extern boolean fuel_l_active;

extern float water_temp;
extern boolean water_temp_active;

extern boolean speed_available;
extern int speed;
extern int altitude;

extern byte hour;
extern byte minute;
extern byte second;
extern byte day;
extern byte month;
extern byte year;

extern float trip_distance;
//extern float trip_distance_tmp;
extern unsigned long trip_timer;

extern boolean gps_available;
extern int gps_satellites;
extern float gps_latitude;
extern long gps_latitude_long;
extern float gps_longitude;
extern long gps_longitude_long;
extern short gps_altitude;

extern float gps_latitude_old;
extern float gps_longitude_old;

extern boolean summer_time;
extern int timezone;
//extern byte timezone_gmt;

extern boolean display_active;
extern boolean display_block;
extern boolean display_menu_set;


extern boolean can_active;
extern unsigned int trip1;
extern boolean trip1_active;

extern unsigned int trip2;
extern boolean trip_day_active;

// configuration variable
extern byte contrast;
extern byte autoswitch;
extern byte speed_offset;
