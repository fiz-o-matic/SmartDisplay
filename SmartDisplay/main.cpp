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
#include "main.h"

#include <OneWire.h>


void setup() {
  Serial.begin(9600);

  delay(3000);
  DEBUG_PRINTLN("init start");

  pinMode(KEY, INPUT);       // Pin 2 ist INT0
  digitalWrite(KEY, HIGH);   // interner Pull up Widerstand auf 5V
  //attachInterrupt(digitalPinToInterrupt(KEY), key_interrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(KEY), key_interrupt, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(KEY), key_released_interrupt, RISING);
  DEBUG_PRINTLN("init TinyGPS");
  tinyGPS_init();
  //DEBUG_PRINTLN("init CAN");
  //can_init();
  DEBUG_PRINTLN("init 1Wire");
  onewire_init();
  DEBUG_PRINTLN("init Input");
  input_init();

  // enable Watchdog
  #ifdef ARDUINO_ARCH_MEGAAVR
  Serial.println("init Watchdog");
  if (RSTCTRL.RSTFR & RSTCTRL_WDRF_bm) {
    Serial.println(F("It was a watchdog reset."));
  }
  RSTCTRL.RSTFR |= RSTCTRL_WDRF_bm ;
  wdt_enable(WDT_PERIOD_8KCLK_gc);
  #else if
  wdt_enable(WDTO_8S);   // Watchdog auf 1 s stellen
  #endif

  DEBUG_PRINTLN("init Display");
  display_init();
  

  DEBUG_PRINTLN("init finished");

}

void loop() {
  // run the tinyGPS Loop
  #ifdef GPS_ENABLED
  tinyGPS_loop();
  #endif

  // run the Display Loop
  display_loop();

  // run the OneWire Loop
  onewire_loop();

  // run the CAN Loop
  //can_loop();

  // read Input ports
  input_loop();

  // reset Watchdog
  wdt_reset();


}




void key_low_interrupt() {
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
}

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



/*
  returns TRUE if millis() is greather then timer + delay
*/
bool timer_check(unsigned long *timer, unsigned long delay)
{

  if ( *timer + delay < millis() ) {

    *timer = millis();

    return true;
  }
  if ( *timer > millis() ) {
    *timer = millis();
    return true;
  }

  return false;
}


bool millisRollover() {
  // found at:
  // https://www.faludi.com/2007/12/18/arduino-millis-rollover-handling/

  // get the current millis() value for how long the microcontroller has been running
  //
  // To avoid any possiblity of missing the rollover, we use a boolean toggle that gets flipped
  //   off any time during the first half of the total millis period and
  //   then on during the second half of the total millis period.
  // This would work even if the function were only run once every 4.5 hours, though typically,
  //   the function should be called as frequently as possible to capture the actual moment of rollover.
  // The rollover counter is good for over 35 years of runtime. --Rob Faludi http://rob.faludi.com
  //
  //static int numRollovers=0; // variable that permanently holds the number of rollovers since startup
  static boolean readyToRoll = false; // tracks whether we've made it halfway to rollover
  unsigned long now = millis(); // the time right now
  unsigned long halfwayMillis = 2147483647; // this is halfway to the max millis value (17179868 for earlier versions of Arduino)

  if (now > halfwayMillis) { // as long as the value is greater than halfway to the max
    readyToRoll = true; // you are ready to roll over
  }

  if (readyToRoll == true && now < halfwayMillis) {
    // if we've previously made it to halfway
    // and the current millis() value is now _less_ than the halfway mark
    // then we have rolled over
    readyToRoll = false; // we're no longer past halfway

    return true;

  }
  else {
    return false;
  }
}
