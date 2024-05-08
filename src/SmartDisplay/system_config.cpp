/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic SmartDisplay
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/

#include "system_config.h"



void read_eeprom_config() {
    DEBUG_PRINT("=== EEPROM Settings ===");
    EEPROM.get(EEPROM_VAL_CONTRAST, contrast);
    DEBUG_PRINT("Contrast: " + String(contrast));
    if ( contrast > 10 ) contrast = 4;
    EEPROM.get(EEPROM_VAL_AUTOSWITCH, autoswitch);
    EEPROM.get(EEPROM_VAL_SPEEDOFFSET, speed_offset);
}

void save_eeprom_config() {
    EEPROM.put(EEPROM_VAL_CONTRAST, contrast);
    EEPROM.put(EEPROM_VAL_AUTOSWITCH, autoswitch);
    EEPROM.put(EEPROM_VAL_SPEEDOFFSET, speed_offset);
}