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
    EEPROM.get(EEPROM_VAL_CONTRAST, contrast);
}

void save_eeprom_config() {
    EEPROM.put(EEPROM_VAL_CONTRAST, contrast);
}