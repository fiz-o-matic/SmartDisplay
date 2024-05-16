// EEPROM lifetime is 100,000 write cycles.
// With 16 values in EEPROM and write every km max. 
// EEPROM Lifetime is 1,600,000 km

// number of values in eeprom
#define EEPROM_VAL_TRIP1 16

// EEPROM Config addresses
#define EEPROM_VAL_CONTRAST EEPROM_VAL_TRIP1*4 + 1
#define EEPROM_VAL_AUTOSWITCH EEPROM_VAL_CONTRAST + 1
#define EEPROM_VAL_SPEEDOFFSET EEPROM_VAL_AUTOSWITCH + 1