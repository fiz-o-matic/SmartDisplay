/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/


#include "key.h"



/*void key_low_interrupt() {
  if ( key_pressed == 0 ) {
    key_pressed = millis();
  }
  else if ( (key_pressed + 100) <= millis() ) {
    MainMenuPos++;
    key_pressed = millis() + 200;
  }
  else {
    delay(50);
  }
}

void key_released_interrupt() {
  if ( ( key_pressed + 200 ) <= millis() ) {
    key_pressed = 0;
  }
}*/

void key_interrupt() {

  if ( digitalRead(KEY) == LOW ) {
    if ( timer_check(&key_timer, (KEY_DEBOUNCE*3) ) ) {
      key_pressed = millis();
      
    }
  }
  else {
    if ( (key_pressed + KEY_DEBOUNCE) <= millis() ) {
      if (!display_active) {
        reset_display_pwrsave();
      }
      else {
        MainMenuPos++;
        reset_display_pwrsave();
      }
      key_pressed = millis();
    }
  }
  display_loop();
}


void key_loop() {
    if ( digitalRead(KEY) == LOW ) {
        if ( (key_pressed + KEY_DEBOUNCE) <= millis() ) {
            DEBUG_PRINTLN(F("KEY pressed..."));

        }
        if ( (key_pressed + KEY_LONGPRESS) <= millis() ) {
            DEBUG_PRINTLN(F("KEY LONG pressed..."));
            
            longpress_active = true;
        }
        if ( longpress_active ) {
            key_pressed = millis() + 10000;
            longpress_active = false;

            if ( MainMenuPos == MENU_trip ) {
                reset_trip();
            }
        }
    }
}