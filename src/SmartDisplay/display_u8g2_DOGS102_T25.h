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


#define LAYOUT_VALUES_DESC 5, 14
#define LAYOUT_VALUES_VALUE 0, 24
#define LAYOUT_VALUES_SUFFIX 80, 24

#define LAYOUT_2VALUES_DESC 5, 14
#define LAYOUT_2VALUES_VALUE1 20, 22
#define LAYOUT_2VALUES_VALUE2 20, 34
//#define LAYOUT_2VALUES_VALUE3 0, 42
#define LAYOUT_2VALUES_SUFFIX1 80, 22
#define LAYOUT_2VALUES_SUFFIX2 80, 34

#define LAYOUT_GPS_DESC 5, 14
#define LAYOUT_GPS_VALUE1 0, 22
#define LAYOUT_GPS_VALUE2 0, 32
#define LAYOUT_GPS_VALUE3 0, 42

#define LAYOUT_INFO_PRODUCT 0, 14
#define LAYOUT_INFO_FIZ_O_MATIC 0, 22
#define LAYOUT_INFO_SW 0, 30
#define LAYOUT_INFO_HW 0, 38

#define LAYOUT_CONFIG_DESC 5, 14
#define LAYOUT_CONFIG_VALUE 24, 24
//#define LAYOUT_CONFIG_SUFFIX 80, 24


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


#define LOGO_width 90
#define LOGO_height 36
#define LOGO_Xpos 6
#define LOGO_Ypos 12
static const unsigned char logo[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x33, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x07, 0x0e, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x0d, 0x0b, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x8e, 0x0d, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe7, 0xcc, 0x8e, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x67, 0xe6, 0x26, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x31, 0x73, 0x66, 0x13, 0x02,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xfe, 0x19, 0x33, 0x73, 0x08, 0x02,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xdf, 0x9c, 0x3b, 0x73, 0x0c, 0x02,
  0x00, 0x00, 0x01, 0x00, 0x00, 0xc0, 0xcc, 0x8c, 0x99, 0x7b, 0x03, 0x03,
  0x00, 0x9c, 0x03, 0x00, 0x1e, 0xe0, 0xee, 0xce, 0xdd, 0xf7, 0x01, 0x01,
  0x00, 0x96, 0x01, 0x00, 0x1b, 0x60, 0x66, 0xc6, 0xbe, 0x03, 0x80, 0x01,
  0x00, 0x1b, 0xf0, 0x80, 0x19, 0x76, 0x77, 0xe7, 0x1f, 0x00, 0xc0, 0x00,
  0x80, 0x1d, 0x6c, 0xc0, 0x98, 0x37, 0xb3, 0xfe, 0x00, 0x00, 0x60, 0x00,
  0xc0, 0xee, 0x78, 0xc0, 0x0c, 0xb8, 0xf3, 0x06, 0x00, 0x00, 0x38, 0x00,
  0xc0, 0x76, 0x1c, 0x6f, 0x0c, 0xb8, 0x33, 0x00, 0x00, 0x00, 0x1e, 0x00,
  0xe0, 0x68, 0x0e, 0x67, 0x06, 0x38, 0x03, 0x00, 0x00, 0xe0, 0x0f, 0x00,
  0x60, 0x36, 0x07, 0x70, 0x03, 0x00, 0x00, 0x00, 0x80, 0xff, 0x03, 0x00,
  0xf0, 0x31, 0x0f, 0xf0, 0x01, 0x00, 0xc0, 0xff, 0xff, 0xff, 0x00, 0x00,
  0xb0, 0x98, 0x1c, 0x60, 0x00, 0xe0, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00,
  0xb8, 0x5c, 0x1c, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00,
  0x98, 0xfc, 0x0d, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00,
  0x5c, 0xdc, 0x0e, 0x00, 0xfe, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00,
  0x4c, 0xe0, 0x06, 0x80, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x2e, 0x60, 0x03, 0xe0, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x36, 0xa0, 0x01, 0xf8, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x16, 0xe0, 0x00, 0xfc, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x80, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc0, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xf0, 0xfd, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#endif