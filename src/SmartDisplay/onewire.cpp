/****************************************************
 * FIZ-o-matic
 * https://fiz-o-matic.net/
 *
 *  This sketch is for OneWire functions.
 *  http://www.hobbytronics.co.uk/ds18b20-arduino
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/

#include <Arduino.h>
#include "config.h"
#include "hardware.h"
#include "vars_global.h"


#ifdef ONEWIRE

//#include <DallasTemperature.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//boolean temp_out_active = false;


OneWire oneWire(18);
DallasTemperature sensors(&oneWire);


void onewire_init() {
  pinMode(18,OUTPUT);
  digitalWrite(18,HIGH);
  delay(10);
  digitalWrite(18, LOW);
  delay(10);

  pinMode(18,INPUT);
  digitalWrite(18, LOW);


  sensors.begin();

  Serial.println(sensors.getDeviceCount(), DEC);
  sensors.requestTemperatures(); // Send the command to get temperatures

    //temp_out_int = sensors.getTempCByIndex(0);

    if (sensors.getTempCByIndex(0) != -127 ) {
      temp_out_active = true;
      DEBUG_PRINTLN("Found 1Wire Sensor");
    }
    else {
      DEBUG_PRINTLN("No 1Wire Sensor found");
    }
}

void onewire_loop() {
  if (temp_out_active) {
    sensors.requestTemperatures(); // Send the command to get temperatures
    temp_out = sensors.getTempCByIndex(0);
  }
}

#else
void onewire_init() {
  DEBUG_PRINTLN("1Wire not enabled");
}
void onewire_loop() {}
#endif
