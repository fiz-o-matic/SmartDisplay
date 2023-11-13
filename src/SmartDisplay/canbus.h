#include <Arduino.h>
//#include "config.h"
#include "hardware.h"
//#include "vars_global.h"
#include "can_addr.h"


#include <CAN.h>
//#include "can_vars.h"

#ifndef CANBUS_TIMER
#define CANBUS_TIMER 1000 // 1s
#endif


// from main.cpp
bool timer_check(unsigned long *timer, unsigned long delay);

// from can_receive.cpp
void can_receive(int packetSize);

// from can_send.cpp
void can_send();


boolean can_active = false;
unsigned long canbus_timer = 0;

//boolean can_active = false;
int packetSize = 0;
//unsigned long canbus_timer = 0;
byte can_buff[8];


//unsigned long value = 0;
uint8_t field = 0;
uint8_t field_cnt = 0;
int can_id = 0;

