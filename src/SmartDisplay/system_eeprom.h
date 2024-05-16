// EEPROM lifetime is 100,000 write cycles.
// With 16 values in EEPROM and write every km max. 
// EEPROM Lifetime is 1,600,000 km

// EEPROM Size on atmega4808 = 256 Bytes

// number of values in eeprom
// 16 * 4Byte = 64 Byte
#define EEPROM_VAL_TRIP1 16
#define EEPROM_ADDR_TRIP1 64

// EEPROM Config addresses
#define EEPROM_ADDR_CONTRAST 0
#define EEPROM_ADDR_AUTOSWITCH EEPROM_ADDR_CONTRAST + 1
#define EEPROM_ADDR_SPEEDOFFSET EEPROM_ADDR_AUTOSWITCH + 1

