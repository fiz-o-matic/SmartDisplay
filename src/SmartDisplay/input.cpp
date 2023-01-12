/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/

#include "input.h"



void input_init() {
  pinMode(IN1, INPUT);
}

void input_loop() {
  if ( !timer_check(&io_timer, IO_TIMER) ) return;

  a3_sum = analogRead(IN1);
  a3_tmp[IO_ARRAY-1] = a3_sum;

  for (i = 0; i < IO_ARRAY-1; i++) {
    a3_tmp[i] = a3_tmp[i+1];
    a3_sum += a3_tmp[i];
  }
  a3 = a3_sum / IO_ARRAY;

  //Serial.println(a3, DEC);

  //bord_voltage = float(map(analogRead(IN1), 0, 1023, 0, 23300)) / 1000;
  bord_voltage_int = float(map(a3, 0, 1023, 0, 23280)) / 1000;
  //bord_voltage_int = float(a3 * A3_MULTIPLICATOR * VOLTAGE_MULTIPLICATOR_CALIBRATION);
  //Serial.println(analogRead(IN1), DEC);
  bord_voltage_int = bord_voltage_int * VOLTAGE_CALIBRATION;
  //DEBUG_PRINTLN(bord_voltage_int);



  if ( bord_voltage_int > TURN_ON_VOLTAGE ) {
    reset_display_pwrsave();
    if ( !engine_running ) {
      MainMenuPos = MENU_speed;
      engine_running = true;
    }
  }
  else {
    if ( engine_running ) {
      MainMenuPos = MENU_clock;
      engine_running = false;
    }
  }

}
