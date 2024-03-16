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
        //MainMenuPos++;
        key_short();
        reset_display_pwrsave();
      }
      key_pressed = millis();
    }
  }
  //display_loop();
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

            key_long();
            /*#ifdef MENU_trip
            if ( MainMenuPos == MENU_trip ) {
                reset_trip();
            }
            #endif*/
        }
    }
}


void key_short() {
    switch (MainMenuPos) {
        #ifdef MENU_Info
        case MENU_Info:
            MainMenuPos = MENU_clock;
            break;
        case MENU_Info + 1:
            DEBUG_PRINTLN("Contrast : " + String(contrast));
            contrast++;
            if ( contrast > 10 ) contrast = 1;
            break;
        #endif
        default: 
            MainMenuPos++;
            break;
    }
}

void key_long() {
    switch (MainMenuPos) {
        #ifdef MENU_trip
        case MENU_trip:
            reset_trip();
            break;
        #endif
        #ifdef MENU_Info
        case MENU_Info:
            MainMenuPos = MENU_Info + 1;
            break;
        case MENU_Info+1:
            save_eeprom_config();
            MainMenuPos = MENU_clock;
            break;
        #endif
        default: 
            MainMenuPos++;
            break;
        
    }
}