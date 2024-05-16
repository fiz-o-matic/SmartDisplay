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
//#include "config.h"
#include "SmartDisplay.ino"
#include "hardware.h"
#include "vars_global.h"


// from display...
void reset_display_pwrsave();
// from main.cpp
bool timer_check(unsigned long *timer, unsigned long delay);


// Number of values for an average
#define IO_ARRAY 10


long a_sum = 0;
int a_tmp[IO_ARRAY];
int a = 0;
int i = 0;

#define IO_TIMER 500 // 1s
unsigned long io_timer = 0;