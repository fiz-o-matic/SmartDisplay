/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * Layout and Logo for
 * OLED with SH1106 controller
 * with croped Layout for VW T3/T25/Vanagon Instrument Cluster
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/
#include <Arduino.h>
#include "config.h"
#include "hardware.h"
#include "vars_global.h"


#ifdef DOGS102_T25

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8G2_UC1701_EA_DOGS102_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ DISPLAY_CS, /* dc=*/ DISPLAY_DC, /* reset=*/ DISPLAY_RST);

#define small_font u8g2_font_profont10_tf
#define small_font_high 8
#define medium_font u8g2_font_profont12_tf
#define medium_font_high 10
#define big_font u8g2_font_profont29_tn
#define big_font_high 24



//#define LAYOUT_CLOCK_1 24, 16
//#define LAYOUT_CLOCK_2 42, 48


//#define LAYOUT1_1_X 128/2 + 0 - 40
//#define LAYOUT1_1_Y 48/2 + 16 - 24/2 - 12
//#define LAYOUT1_2_X LAYOUT1_1_X
//#define LAYOUT1_2_Y LAYOUT1_1_Y + big_font_high

#define LAYOUT_CLOCK_CLOCK 12, 14
#define LAYOUT_CLOCK_TEMP 30, 36
#define LAYOUT_CLOCK_NO_TEMP 12, 20

#define LAYOUT_SPEED_SPEED 24, 14
#define LAYOUT_SPEED_KMH 72, 14
#define LAYOUT_SPEED_CLOCK 2, 38
#define LAYOUT_SPEED_TEMP 60, 38
#define LAYOUT_SPEED_CLOCK_NO_TEMP 36, 38


#define LAYOUT_VALUES_DESC 0, 14
#define LAYOUT_VALUES_VALUE 0, 24
#define LAYOUT_VALUES_SUFFIX 80, 24

#define LAYOUT_2VALUES_DESC 0, 14
#define LAYOUT_2VALUES_VALUE1 0, 22
#define LAYOUT_2VALUES_VALUE2 0, 32
#define LAYOUT_2VALUES_VALUE3 0, 42
//#define LAYOUT_2VALUES_SUFFIX 98, 32

#define LAYOUT_INFO_PRODUCT 0, 14
#define LAYOUT_INFO_FIZ_O_MATIC 0, 22
#define LAYOUT_INFO_SW 0, 30
#define LAYOUT_INFO_HW 0, 38


/*#define MACRO_DISPLAY_VALUE(DESC, VALUE, DIGITS, SUFFIX) ({\
  u8g2.setFont(small_font);\
  u8g2.setFontPosTop();\
  u8g2.setCursor(0, 16);\
  u8g2.print(F(DESC));\
  u8g2.setCursor(0, 32);\
  u8g2.setFont(big_font);\
  u8g2.setCursor(0, 32);\
  if ( VALUE <= 10 ) {\
    u8g2.print(F("   "));\
  }\
  else if ( VALUE <= 100 ) {\
    u8g2.print(F("  "));\
  }\
  else if ( VALUE <= 1000 ) {\
    u8g2.print(F(" "));\
  }\
  if ( DIGITS != 1 ) {\
    u8g2.print(F("  "));\
  }\
  u8g2.print(VALUE,DIGITS);\
  u8g2.setFont(medium_font);\
  u8g2.setCursor(98, 32);\
  u8g2.print(F(SUFFIX));\
})*/



#endif
