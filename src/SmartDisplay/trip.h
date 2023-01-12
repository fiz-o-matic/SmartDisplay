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
#include "vars_global.h"


float trip_distance_tmp = 0;

// from main.cpp
bool timer_check(unsigned long *timer, unsigned long delay);

// local 
float get_distance(float latitude1, float longitude1, float latitude2, float longitude2);