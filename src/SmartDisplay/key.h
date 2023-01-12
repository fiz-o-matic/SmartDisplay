/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/


#include "config.h"
#include "hardware.h"
//#include "can_vars.h"
//#include "vars.h"
#include "vars_global.h"




// from display.cpp
void display_init(void);
void display_loop();
void reset_display_pwrsave();

// from main.cpp
bool timer_check(unsigned long *timer, unsigned long delay);

// from trip.cpp
void reset_trip();


volatile unsigned long last_key=0;
unsigned long key_timer = 0;

unsigned long key_pressed = 0;
unsigned long key_released = 0;

boolean longpress_active = false;
