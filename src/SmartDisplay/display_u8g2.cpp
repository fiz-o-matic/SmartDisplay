/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************
 *  This code is based on the U8G2 library from olikraus.
 *  GIT: https://github.com/olikraus/u8g2
 *       https://github.com/olikraus/U8g2_Arduino
 *  Wiki: https://github.com/olikraus/u8g2/wiki
 *
 *
 ****************************************************/
#include <Arduino.h>
#include "display_u8g2.h"
#include "vars_global.h"
#include "canvalues.h"

#ifdef U8G2_DISPLAY

#include <U8g2lib.h>

char buf[64]; 
int i_tmp = 0;


void display_init(void) {
    u8g2.begin();
    u8g2.enableUTF8Print();
    //u8g2.setContrast(20);
    clear_screen();
    menu_logo();
}


void display_loop() {
    // turn off OLED Display on Standby
    #if defined SH1107 || defined SH1106_T25
    if ( timer_check(&display_timeout, DISPLAY_TIMEOUT) ) {
        display_pwrsave(true);
        MainMenuPos = 1;
        //MainMenuPos++;
        clear_screen();
    }
    #endif

    if ( !display_block ) {
        display_block = true;
        display();
        display_block = false;
    }
    #ifdef CAN_CS
    if ( !digitalRead(CAN_CS) ) {
            DEBUG_PRINT("SPI BUS is used for CAN. Try ist next time...")
            digitalWrite(DISPLAY_CS, HIGH);
        }
    #endif

    u8g2.setContrast(contrast * 10);
}


void reset_display_pwrsave() {
  if (!display_active) {
    display_pwrsave(false);
  }
  display_timeout = millis();
}

void display_pwrsave(bool pwrsave) {
  u8g2.setPowerSave(pwrsave);
  u8g2.sendBuffer();					// transfer internal memory to the display
  display_active = !pwrsave;
}

void clear_screen() {
  u8g2.clearBuffer();
  u8g2.clearDisplay();
}




/*
 * Display MENUs
 */
void display() {
    // display_menu_set is needed to skip menu entries
    display_menu_set = false;

    while(!display_menu_set) {

        if ( OldPos != MainMenuPos ) {
        clear_screen();
        OldPos = MainMenuPos;
        }
        //DEBUG_PRINT(String(MainMenuPos));

        switch (MainMenuPos) {
            case MENU_clock:
                //DEBUG_PRINT("MENU_clock");
                menu_clock();
                //menu_logo();
                display_menu_set = true;
                break;
            #ifdef MENU_speed
            case MENU_speed:
                //DEBUG_PRINT("MENU_speed");
                menu_speed(STR_SPEED, speed, DEC, "km/h");
                display_menu_set = true;
                break;
            #endif
            #ifdef MENU_temp
            case MENU_temp:
                if ( water_temp_active ) {
                menu_values(STR_WATER_TEMP, water_temp, 1, "\xb0 C");
                display_menu_set = true;
                } else MainMenuPos++;
                break;
            #endif
            #ifdef MENU_fuel
            case MENU_fuel:
                if ( fuel_l_active ) {
                menu_values(STR_FUEL, fuel_l, 0, "l");
                display_menu_set = true;
                } else MainMenuPos++; break;
            #endif
            #ifdef MENU_oil_temp
            case MENU_oil_temp:
                if ( oil_temp_active ) {
                menu_values(STR_OIL_TEMP, oil_temp, 0, "\xb0 C");
                display_menu_set = true;
                } else MainMenuPos++;
                break;
            #endif
            #ifdef MENU_oil_pressure
            case MENU_oil_pressure:
                if ( oil_pressure_active ) {
                menu_values(STR_OIL_PRESSURE, oil_pressure, 1, "bar");
                display_menu_set = true;
                } else MainMenuPos++;
                break;
            #endif
            #ifdef MENU_batt1_voltage
            case MENU_batt1_voltage:
                if ( batt1_voltage_active ) {
                menu_values(STR_BATT1, batt1_voltage, 1, "V");
                display_menu_set = true;
                } else MainMenuPos++;
                break;
            #endif
            #ifdef MENU_batt2_voltage
            case MENU_batt2_voltage:
                if ( batt2_voltage_active ) {
                menu_values(STR_BATT2, batt2_voltage, 1, "V");
                display_menu_set = true;
                } else MainMenuPos++;
                break;
            #endif
            #ifdef MENU_bord_voltage
            case MENU_bord_voltage:
                if ( bord_voltage_active ) {
                menu_values(STR_BORD_VOLT, bord_voltage, 1, "V");
                display_menu_set = true;
                } else MainMenuPos++;
                break;
            #endif
            #ifdef MENU_bord_voltage_int
            case MENU_bord_voltage_int:
                menu_values(STR_BORD_VOLT_INT, bord_voltage_int + 0.05, 1, "V");
                display_menu_set = true;
                break;
            #endif
            #ifdef MENU_gps
            case MENU_gps:
                menu_gps_1();
                display_menu_set = true;
                break;
            #endif
            #ifdef MENU_altitude
            case MENU_altitude:
                menu_values(STR_ALTITUTE, gps_altitude, DEC, "m");
                display_menu_set = true;
                break;
            #endif
            #ifdef MENU_rpm
            case MENU_rpm:
                if ( rpm_active ) {
                menu_values(STR_RPM, rpm, DEC, "U/min");
                display_menu_set = true;
                } else MainMenuPos++;
                break;
            #endif
            #ifdef MENU_trip
            case MENU_trip:
                menu_values(STR_TRIP, trip_distance, 1, "km");
                display_menu_set = true;
                break;
            #endif

            #ifdef MENU_CAN
            case MENU_CAN:
                if ( display_req_addr != 0x00 ) {
                menu_can();
                display_menu_set = true;
                }
                else {
                MainMenuPos++;
                }
                break;
                
                break;
            #endif

            #ifdef MENU_CAN_NEXT
            case MENU_CAN_NEXT:
                if ( can_next() ) {
                MainMenuPos = MENU_CAN; 
                //delay(500);
                }
                else {
                MainMenuPos++;
                }
                break;
            #endif

            #ifdef MENU_Info
            case MENU_Info:
                menu_info();
                display_menu_set = true;
                break;

            case MENU_Info + 1:
                menu_config(STR_CONTRAST, contrast);
                display_menu_set = true;
                break;
            case MENU_Info + 2:
                menu_config(STR_AUTOSWITCH, autoswitch);
                display_menu_set = true;
                break;
            case MENU_Info + 3:
                menu_config(STR_SPEEDOFFSET, speed_offset);
                display_menu_set = true;
                break;
            #endif


            default: 
                menu_clock();
                MainMenuPos = 1;
                display_menu_set = true;
                break;
            
        }

    }
    //} while ( u8g2.nextPage() );

}


void menu_logo() {
	noInterrupts();
	u8g2.firstPage();
  	do {
		u8g2.drawXBM(LOGO_Xpos, LOGO_Ypos, LOGO_width, LOGO_height, logo);
	} while ( u8g2.nextPage() );
	interrupts();
}

/*
 * simple clock with date
 */
void menu_clock() {
  noInterrupts();
  int m;
  //clear_screen();
  u8g2.firstPage();
  do {
    u8g2.clearBuffer();
    u8g2.setFont(big_font);
    u8g2.setFontPosTop();
    
    if ( temp_out_active ) {
      u8g2.setCursor(LAYOUT_CLOCK_CLOCK);
      sprintf(buf, "%02d:%02d", hour, minute);
      u8g2.print(buf);

      u8g2.setFont(medium_font);
      u8g2.setFontPosTop();
      u8g2.setCursor(LAYOUT_CLOCK_TEMP);
    
      dtostrf(temp_out, 5, 1, buf);
      u8g2.print(buf);
      //u8g2.print(temp_out, 1);
      u8g2.print(F("\xb0"));
      u8g2.print(F("C"));
    }
    else {
      u8g2.setCursor(LAYOUT_CLOCK_NO_TEMP);
      sprintf(buf, "%02d:%02d", hour, minute);
      u8g2.print(buf);
    }
  } while ( u8g2.nextPage() );

  interrupts();
}

void menu_speed(int DESC, float VALUE, byte DIGITS, String SUFFIX) {
  int m;
  noInterrupts();
  u8g2.firstPage();
  do {
    u8g2.clearBuffer();
    u8g2.setFontPosTop();

    /*u8g2.setFont(small_font);
    u8g2.setFontPosTop();
    u8g2.setCursor(0, 16);
    //u8g2.print(DESC);
    print_string(DESC);*/
    u8g2.setCursor(LAYOUT_SPEED_SPEED);
    u8g2.setFont(big_font);
    if ( speed_available ) {
      dtostrf(speed, 3, 0, buf);
      //sprintf (buf, "%3d", (int)speed);
      u8g2.print(buf);
    }
    else {
      u8g2.print("---");
    }
    

    u8g2.setCursor(LAYOUT_SPEED_KMH);
    u8g2.setFont(medium_font);
    u8g2.print(F("km/h"));


    if ( temp_out_active ) {
      u8g2.setFont(medium_font);
      u8g2.setCursor(LAYOUT_SPEED_CLOCK);
      sprintf(buf, "%02d:%02d", hour, minute);
      u8g2.print(buf);

      u8g2.setCursor(LAYOUT_SPEED_TEMP);
      dtostrf(temp_out, 5, 1, buf);
      u8g2.print(buf);
      u8g2.print(F("\xb0"));
      u8g2.print(F("C"));
    }
    else {
      u8g2.setFont(medium_font);
      u8g2.setCursor(LAYOUT_SPEED_CLOCK_NO_TEMP);
      sprintf(buf, "%02d:%02d", hour, minute);
      u8g2.print(buf);
    }
  } while ( u8g2.nextPage() );
  interrupts();
}


void menu_values(int DESC, float VALUE, byte DIGITS, String SUFFIX) {
  noInterrupts();
  if ( DIGITS == 1 ) {
    //i_tmp = (VALUE - ( (int) VALUE ))*10;
    //sprintf (buf, "%3d.%1d", (int)VALUE, i_tmp);
    dtostrf(VALUE, 5, 1, buf);
  }
  else if ( DIGITS == 2 ) {
    //i_tmp = (VALUE - ( (int) VALUE ))*100;
    //sprintf (buf, "%2d.%02d", (int)VALUE, i_tmp);
    dtostrf(VALUE, 5, 2, buf);
  }
  else {
    sprintf (buf, "%5d", (int)VALUE);
    dtostrf(VALUE, 5, 0, buf);
  }


  u8g2.firstPage();
  do {
    u8g2.clearBuffer();

    u8g2.setFont(small_font);
    u8g2.setFontPosTop();

    u8g2.setCursor(LAYOUT_VALUES_DESC);
    print_string(DESC);

    u8g2.setFont(big_font);
    u8g2.setCursor(LAYOUT_VALUES_VALUE);
    u8g2.print(buf);
    u8g2.setFont(medium_font);

    u8g2.setCursor(LAYOUT_VALUES_SUFFIX);
    u8g2.print(SUFFIX);
  } while ( u8g2.nextPage() );
  interrupts();
}

void menu_2values(int DESC, long VALUE1, byte DIGITS1, String SUFFIX1, long VALUE2, byte DIGITS2, String SUFFIX2) {
  noInterrupts();
  u8g2.firstPage();
  do {
    u8g2.clearBuffer();

    u8g2.setFont(small_font);
    u8g2.setFontPosTop();
    u8g2.setCursor(LAYOUT_2VALUES_DESC);
    print_string(DESC);

    u8g2.setFont(small_font);
    u8g2.setCursor(LAYOUT_2VALUES_VALUE1);
    print_string(STR_LAT);
    u8g2.print(F("  : "));
    u8g2.print(gps_latitude,6);

    u8g2.setCursor(LAYOUT_2VALUES_VALUE2);
    print_string(STR_LONG);
    u8g2.print(F(" : "));
    u8g2.print(gps_longitude,6);

  } while ( u8g2.nextPage() );
  interrupts();
}


void menu_values(char DESC[18], char VALUE[9], char SUFFIX[5]) {
  noInterrupts();

  u8g2.firstPage();
  do {
    u8g2.clearBuffer();

    u8g2.setFont(small_font);
    u8g2.setFontPosTop();

    u8g2.setCursor(LAYOUT_VALUES_DESC);
    //print_string(DESC);
	u8g2.print(DESC);

    u8g2.setFont(big_font);
    u8g2.setCursor(LAYOUT_VALUES_VALUE);
    //u8g2.print(buf);
	u8g2.print(VALUE);
    u8g2.setFont(medium_font);

    u8g2.setCursor(LAYOUT_VALUES_SUFFIX);
    u8g2.print(SUFFIX);
  } while ( u8g2.nextPage() );
  interrupts();
}

void menu_2values(char DESC[18], char VALUE1[9], char SUFFIX1[5], char VALUE2[9], char SUFFIX2[5]) {
	noInterrupts();
  	u8g2.firstPage();
  	do {
		u8g2.clearBuffer();

		u8g2.setFont(small_font);
		u8g2.setFontPosTop();
		u8g2.setCursor(LAYOUT_2VALUES_DESC);
		u8g2.print(DESC);

		u8g2.setFont(small_font);
		u8g2.setCursor(LAYOUT_2VALUES_SUFFIX1);
    	u8g2.print(SUFFIX1);
		u8g2.setCursor(LAYOUT_2VALUES_SUFFIX2);
    	u8g2.print(SUFFIX2);

		u8g2.setFont(medium_font);
		u8g2.setCursor(LAYOUT_2VALUES_VALUE1);
		u8g2.print(VALUE1);
		u8g2.setCursor(LAYOUT_2VALUES_VALUE2);
		u8g2.print(VALUE2);
		

	} while ( u8g2.nextPage() );
  	interrupts();
}

void menu_can() {
  //CAN.hase();
  //DEBUG_PRINT("CAN Menue...");
  //byte pos = 0;

	if ( display_msg_type == MSG_TYPE_1VALUE ) {
	  	menu_values(display_desc, display_value1, display_value1_suffix);
	}
	else if ( display_msg_type == MSG_TYPE_2VALUES ) {
		menu_2values(display_desc, display_value1, display_value1_suffix, display_value2, display_value2_suffix);
	}
	else {
		menu_values(display_desc, display_value1, display_value1_suffix);
	}

  /*noInterrupts();

  u8g2.firstPage();
  do {
    u8g2.clearBuffer();

    u8g2.setFont(small_font);
    u8g2.setFontPosTop();

    u8g2.setCursor(LAYOUT_VALUES_DESC);
    //print_string(DESC);
    //u8g2.print(can_value_name1);
    u8g2.print(display_desc);

    u8g2.setFont(big_font);
    u8g2.setCursor(LAYOUT_VALUES_VALUE);
    //u8g2.print(buf);

    //DEBUG_PRINT(String(strlen(can_value), DEC));
    
	u8g2.print(display_value1);
    u8g2.setFont(medium_font);

    u8g2.setCursor(LAYOUT_VALUES_SUFFIX);
    //u8g2.print(SUFFIX);
	if ( strcmp(display_value1_suffix, "°C") == 0) {
        u8g2.print(F("\xb0"));
      	u8g2.print(F("C"));
    }
	else {
		u8g2.print(display_value1_suffix);
	}
    
  } while ( u8g2.nextPage() );
  interrupts();*/
}


void menu_gps_1() {
  noInterrupts();
  u8g2.firstPage();
  do {
    u8g2.clearBuffer();

    u8g2.setFont(small_font);
    u8g2.setFontPosTop();
    u8g2.setCursor(LAYOUT_GPS_DESC);
    //u8g2.print(DESC);
    print_string(STR_COORDINATES);
    u8g2.setCursor(LAYOUT_GPS_VALUE1);
    u8g2.setFont(small_font);
    if ( gps_available ) {
      //u8g2.setCursor(0, 32);
      print_string(STR_LAT);
      u8g2.print(F(" : "));
      u8g2.print(gps_latitude,6);

      u8g2.setCursor(LAYOUT_GPS_VALUE2-2);
      print_string(STR_LONG);
      u8g2.print(F(": "));
      u8g2.print(gps_longitude,6);

      u8g2.setCursor(LAYOUT_GPS_VALUE3-4);
      print_string(STR_SATELITES);
      u8g2.print(F(": "));
      u8g2.print(gps_longitude,0);
    }
    else {
      print_string(STR_NOGPS);
      u8g2.setCursor(LAYOUT_GPS_VALUE2);
      u8g2.print("reset in : " + String(tinyGPS_watchdog_reset_in()) + "s");
    }

  } while ( u8g2.nextPage() );
  interrupts();
}

void menu_info() {
  noInterrupts();
  u8g2.firstPage();
  do {
    u8g2.clearBuffer();

    u8g2.setFont(small_font);
    u8g2.setFontPosTop();
    u8g2.setCursor(LAYOUT_INFO_PRODUCT);
    u8g2.print(F("    SmartDisplay"));
    u8g2.setCursor(LAYOUT_INFO_FIZ_O_MATIC);
    u8g2.print(F(" @fiz-o-matic.net"));
    
    u8g2.setCursor(LAYOUT_INFO_SW);
    u8g2.print(F("SW: "));
    u8g2.print(F(VERSION_SW));
    u8g2.print(F(" ("));
    u8g2.print(F(BUILD));
    u8g2.print(F(")"));
    u8g2.setCursor(LAYOUT_INFO_HW);
    u8g2.print(F("HW: "));
    u8g2.print(F(VERSION_HW));
  
  } while ( u8g2.nextPage() );
  interrupts();
}

void menu_config(int DESC, byte VALUE) {
  noInterrupts();

  u8g2.firstPage();
  do {
    u8g2.clearBuffer();

    u8g2.setFont(small_font);
    u8g2.setFontPosTop();

    u8g2.setCursor(LAYOUT_CONFIG_DESC);
    print_string(DESC);

    u8g2.setFont(big_font);
    u8g2.setCursor(LAYOUT_CONFIG_VALUE);
    u8g2.print(VALUE);
    u8g2.setFont(medium_font);

  } while ( u8g2.nextPage() );
  interrupts();
}

/*String format(float value, String format) {
  int m = 0;
  if ( value >= 0 ) {
    m = (value - ( (int) value ))*10;
    sprintf (buf, format, (int)value, m);
  }
  else {
    m = (0 - value + ( (int) value ))*10;
    sprintf (buf, format, (int)value, m);
  }
  return buf;
}*/

void print_string(int string_id) {
  switch (string_id) {
    case STR_SPEED: DISPLAY_PRINT(F(STR_SPEED_S)); break;
    case STR_WATER_TEMP: DISPLAY_PRINT(F(STR_WATER_TEMP_S)); break;
    case STR_FUEL: DISPLAY_PRINT(F(STR_FUEL_S)); break;
    case STR_OIL_TEMP: DISPLAY_PRINT(F(STR_OIL_TEMP_S)); break;
    case STR_OIL_PRESSURE: DISPLAY_PRINT(F(STR_OIL_PRESSURE_S)); break;
    case STR_BORD_VOLT: DISPLAY_PRINT(F(STR_BORD_VOLT_S)); break;
    case STR_BATT1: DISPLAY_PRINT(F(STR_BATT1_S)); break;
    case STR_BATT2: DISPLAY_PRINT(F(STR_BATT2_S)); break;
    case STR_RPM: DISPLAY_PRINT(F(STR_RPM_S)); break;
    
    case STR_NOGPS: DISPLAY_PRINT(F(STR_NOGPS_S)); break;
    case STR_ALTITUTE: DISPLAY_PRINT(F(STR_ALTITUTE_S)); break;
    case STR_LAT: DISPLAY_PRINT(F(STR_LAT_S)); break;
    case STR_LONG: DISPLAY_PRINT(F(STR_LONG_S)); break;
    case STR_SATELITES: DISPLAY_PRINT(F(STR_SATELITES_S)); break;
    case STR_BORD_VOLT_INT: DISPLAY_PRINT(F(STR_BORD_VOLT_INT_S)); break;


    case STR_TEMP: DISPLAY_PRINT(F(STR_TEMP_S)); break;
    case STR_OUT: DISPLAY_PRINT(F(STR_OUT_S)); break;
    case STR_IN: DISPLAY_PRINT(F(STR_IN_S)); break;
    case STR_HUMIDITY: DISPLAY_PRINT(F(STR_HUMIDITY_S)); break;
    case STR_COORDINATES: DISPLAY_PRINT(F(STR_COORDINATES_S)); break;
    case STR_TRIP: DISPLAY_PRINT(F(STR_TRIP_S)); break;
    case STR_CONTRAST: DISPLAY_PRINT(F(STR_CONTRAST_S)); break;
    case STR_AUTOSWITCH: DISPLAY_PRINT(F(STR_AUTOSWITCH_S)); break;
    case STR_SPEEDOFFSET: DISPLAY_PRINT(F(STR_SPEEDOFFSET_S)); break;


    case STR_KMH: DISPLAY_PRINT(F(STR_KMH_S)); break;
    case STR_CELCIUS: DISPLAY_PRINT(F(STR_CELCIUS_S)); break;
    case STR_BAR: DISPLAY_PRINT(F(STR_BAR_S)); break;
    case STR_V: DISPLAY_PRINT(F(STR_V_S)); break;
    case STR_L: DISPLAY_PRINT(F(STR_L_S)); break;
    case STR_RPM_SIGN: DISPLAY_PRINT(F(STR_RPM_SIGN_S)); break;
    case STR_M: DISPLAY_PRINT(F(STR_M_S)); break;
  }
}


#endif // U8G2_DISPLAY
