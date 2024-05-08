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

  a_sum = analogRead(IN1);
  a_tmp[IO_ARRAY-1] = a_sum;

  for (i = 0; i < IO_ARRAY-1; i++) {
    a_tmp[i] = a_tmp[i+1];
    a_sum += a_tmp[i];
  }
  a = a_sum / IO_ARRAY;

  //Serial.println(a3, DEC);

  //bord_voltage = float(map(analogRead(IN1), 0, 1023, 0, 23300)) / 1000;
  //bord_voltage_int = float(map(a3, 0, 1023, 0, 23280)) / 1000;
  bord_voltage_int = float(map(a, 0, 1023, 0, VOLTAGE_RANGE_MV)) / 1000;
  //bord_voltage_int = float(a3 * A3_MULTIPLICATOR * VOLTAGE_MULTIPLICATOR_CALIBRATION);
  //DEBUG_PRINT(analogRead(IN1), DEC);
  bord_voltage_int = bord_voltage_int * VOLTAGE_CALIBRATION;
  //DEBUG_PRINT(bord_voltage_int);
  /*DEBUG_PRINT("RAW Input: ");
  DEBUG_PRINT(analogRead(IN1));
  DEBUG_PRINT("VOLTAGE: ");
  DEBUG_PRINT(bord_voltage_int);*/




  /*if ( bord_voltage_int > TURN_ON_VOLTAGE ) {
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
  }*/

}



void engine_state() {

    //DEBUG_PRINT("bord_voltage_int = " + String(bord_voltage_int));
    if ( ( bord_voltage_int > TURN_ON_VOLTAGE ) or ( speed >= 6 ) ) {
        reset_display_pwrsave();
        if ( !engine_running ) {
        //#ifdef DISPLAY_AUTO_SWITCH
        #ifdef MENU_speed
        if ( autoswitch ) {
            //DEBUG_PRINT(F("Switch to speed menu"));
            MainMenuPos = MENU_speed;
        }
        #endif
        //#endif
        engine_running = true;
        }
    }
    else {
        if ( engine_running ) {
        //#ifdef DISPLAY_AUTO_SWITCH
        if ( autoswitch ) {
            //DEBUG_PRINT(F("Switch to clock menu"));
            MainMenuPos = MENU_clock;
        }
        //#endif
        engine_running = false;
        }
    }

    #ifdef DISPLAY_AUTO_SWITCH
    if (speed >= 15 ) {
        
        MainMenuPos = MENU_speed;
        
        engine_running = true;
    }
    #endif


}