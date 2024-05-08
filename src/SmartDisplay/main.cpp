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




void setup() {
    Serial.begin(115200);

    //delay(3000);

    //DEBUG_PRINT("#fiz-o-matic.net ");
    //DEBUG_PRINT("SmartDisplay ");
    DEBUG_PRINT("Version " + String(VERSION_SW));
    //DEBUG_PRINT( F(VERSION_SW));
    DEBUG_PRINT(" Build: " + String(BUILD));
    //DEBUG_PRINT( F(BUILD));

    //DEBUG_PRINT("#Compiled: " + String(__DATE__) + ", " + String(__TIME__) + ", " + String(__VERSION__));
    //DEBUG_PRINT( F(__DATE__));
    //DEBUG_PRINT( F(", "));
    //DEBUG_PRINT( F(__TIME__));
    //DEBUG_PRINT( F(", "));
    //DEBUG_PRINTLN( F(__VERSION__));


    //DEBUG_PRINT("init start");

    DEBUG_PRINT(F("init Display"));
    display_init();

    
    DEBUG_PRINT(F("read EEPROM config"));
    read_eeprom_config();

    DEBUG_PRINT(F("init TinyGPS"));
    GPS_init();

    DEBUG_PRINT(F("init CAN"));
    //can_init();
    can_init();
    
    DEBUG_PRINT(F("init 1Wire"));
    onewire_init();

    DEBUG_PRINT(F("init Input"));
    input_init();
    key_init();


    // enable Watchdog
    #ifdef ARDUINO_ARCH_MEGAAVR
    DEBUG_PRINT("init Watchdog");
    if (RSTCTRL.RSTFR & RSTCTRL_WDRF_bm) {
        DEBUG_PRINT(F("It was a watchdog reset."));
    }
    RSTCTRL.RSTFR |= RSTCTRL_WDRF_bm ;
    wdt_enable(WDT_PERIOD_8KCLK_gc);
    #else if
    wdt_enable(WDTO_8S);   // Watchdog auf 8 s stellen
    #endif

    //DEBUG_PRINT(F("init Display"));
    //display_init();
    

    DEBUG_PRINT(F("read EEPROM"));
    read_eeprom_trip1();
    /*write_eeprom_trip1();
    delay(1000);
    write_eeprom_trip1();
    write_eeprom_trip1();
    write_eeprom_trip1();
    write_eeprom_trip1();
    write_eeprom_trip1();
    write_eeprom_trip1();
    write_eeprom_trip1();
    write_eeprom_trip1();*/
    //clear_eeprom_trip1();
    //delay(10000);

    DEBUG_PRINT(F("init finished"));

}

void loop() {
    // run the tinyGPS Loop
    #ifdef GPS_ENABLED
    GPS_loop();
    //delay(100);
    #endif

    // run the Display Loop
    display_loop();

    // run key handling
    key_loop();

    // run the OneWire Loop
    onewire_loop();

    // run the CAN Loop
    can_loop();
    
    // read Input ports
    input_loop();

    // handle the engine running state
    engine_state();

    // reset Watchdog
    wdt_reset();


}






/*
  returns TRUE if millis() is greather then timer + delay
*/
bool timer_check(unsigned long *timer, unsigned long delay)
{

    if ( *timer == 0 ) {
        *timer = millis();
        return false;
    }
    if ( *timer + delay < millis() ) {
        //DEBUG_PRINTLN("millis()  : " + String(millis(), DEC));
        //DEBUG_PRINTLN("timer val : " + String(*timer, DEC));
        *timer = millis();
        //DEBUG_PRINTLN("new val   : " + String(*timer, DEC));
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
