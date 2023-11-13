//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515 Demo in loopback mode
//——————————————————————————————————————————————————————————————————————————————

#include "hardware.h"
#ifdef CANBUS
#include <ACAN2515.h>
#include "canvalues.h"


#define DISPLAY_ADDR 0x80
char name2[16];
float value = 98.123;
int recv_id = 0;
int recv_type = 0;
int recv_display = 0;
char recv_name1[9];
char recv_name2[9];
char recv_value[9];
//float recv_value = 0;

char can_value_name1[9];
char can_value_name2[9];
char can_value[9];
char can_value_type[8];

byte CAN_DATA[256][8];

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 connections:
//    - standard SPI pins for SCK, MOSI and MISO
//    - a digital output for CS
//    - interrupt input pin for INT
//——————————————————————————————————————————————————————————————————————————————
// If you use CAN-BUS shield (http://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/) with Arduino Uno,
// use B connections for MISO, MOSI, SCK, #9 or #10 for CS (as you want),
// #2 or #3 for INT (as you want).
//——————————————————————————————————————————————————————————————————————————————
// Error codes and possible causes:
//    In case you see "Configuration error 0x1", the Arduino doesn't communicate
//       with the 2515. You will get this error if there is no CAN shield or if
//       the CS pin is incorrect. 
//    In case you see success up to "Sent: 17" and from then on "Send failure":
//       There is a problem with the interrupt. Check if correct pin is configured
//——————————————————————————————————————————————————————————————————————————————

static const byte MCP2515_CS  = CAN_CS ; // CS input of MCP2515 (adapt to your design) 
static const byte MCP2515_INT =  CAN_IRQ ; // INT output of MCP2515 (adapt to your design)

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 Driver object
//——————————————————————————————————————————————————————————————————————————————

ACAN2515 can (MCP2515_CS, SPI, MCP2515_INT) ;

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 Quartz: adapt to your design
//——————————————————————————————————————————————————————————————————————————————

static const uint32_t QUARTZ_FREQUENCY = 16UL * 1000UL * 1000UL ; // 16 MHz


void canISR () {
  //DEBUG_PRINTLN(F("*"));
  can.isr () ;
}

//——————————————————————————————————————————————————————————————————————————————
//   SETUP
//——————————————————————————————————————————————————————————————————————————————

void can_init () {
//--- Switch on builtin led
  //pinMode (LED_BUILTIN, OUTPUT) ;
  //digitalWrite (LED_BUILTIN, HIGH) ;
//--- Start serial
  //Serial.begin (38400) ;
//--- Wait for serial (blink led at 10 Hz during waiting)
  while (!Serial) {
    delay (50) ;
    //digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
//--- Begin SPI
  SPI.begin () ;
//--- Configure ACAN2515
  Serial.println ("Configure ACAN2515") ;
  ACAN2515Settings settings (QUARTZ_FREQUENCY, 50UL * 1000UL) ; // CAN bit rate 125 kb/s
  //settings.mRequestedMode = ACAN2515Settings::LoopBackMode ; // Select loopback mode
  //settings.mReceiveBufferSize = 128 ;
  const uint16_t errorCode = can.begin (settings, canISR) ;
  if (errorCode == 0) {
    Serial.print ("Bit Rate prescaler: ") ;
    Serial.println (settings.mBitRatePrescaler) ;
    Serial.print ("Propagation Segment: ") ;
    Serial.println (settings.mPropagationSegment) ;
    Serial.print ("Phase segment 1: ") ;
    Serial.println (settings.mPhaseSegment1) ;
    Serial.print ("Phase segment 2: ") ;
    Serial.println (settings.mPhaseSegment2) ;
    Serial.print ("SJW: ") ;
    Serial.println (settings.mSJW) ;
    Serial.print ("Triple Sampling: ") ;
    Serial.println (settings.mTripleSampling ? "yes" : "no") ;
    Serial.print ("Actual bit rate: ") ;
    Serial.print (settings.actualBitRate ()) ;
    Serial.println (" bit/s") ;
    Serial.print ("Exact bit rate ? ") ;
    Serial.println (settings.exactBitRate () ? "yes" : "no") ;
    Serial.print ("Sample point: ") ;
    Serial.print (settings.samplePointFromBitStart ()) ;
    Serial.println ("%") ;
  }else{
    Serial.print ("Configuration error 0x") ;
    Serial.println (errorCode, HEX) ;
  }
}

//----------------------------------------------------------------------------------------------------------------------

static uint32_t gBlinkLedDate = 0 ;
static uint32_t gReceivedFrameCount = 0 ;
static uint32_t gSentFrameCount = 0 ;

//——————————————————————————————————————————————————————————————————————————————

void can_loop () {
  char value_type[6];
  CANMessage frame ;
  /*if (gBlinkLedDate < millis ()) {
    gBlinkLedDate += 2000 ;
    //digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    bool ok = can.tryToSend (frame) ;
    if (ok) {
      gSentFrameCount += 1 ;
      Serial.print ("Sent: ") ;
      Serial.println (gSentFrameCount) ;
    }else{
      Serial.println ("Send failure") ;
    }
    unsigned long time_tmp = millis();
    byte timebuffer[4];
    timebuffer[0] = time_tmp >> 24;
    timebuffer[1] = time_tmp >> 16;
    timebuffer[2] = time_tmp >> 8;
    timebuffer[3] = time_tmp;
    frame.id = 0xB1;
    frame.len = 4;
    frame.data[0] = timebuffer[0];
    frame.data[1] = timebuffer[1];
    frame.data[2] = timebuffer[2];
    frame.data[3] = timebuffer[3];

    ok = can.tryToSend (frame) ;
    if (ok) {
        gSentFrameCount += 1 ;
    } else {
        DEBUG_PRINT("Failed to send CAN Data 0xA1");
    }
  }*/


  if (can.available ()) {
    //can.receive (frame) ;
    gReceivedFrameCount ++ ;
    Serial.print ("Received: ") ;
    Serial.println (gReceivedFrameCount) ;
    while (can.receive(frame)) {
            
      String can_frame;
      can_frame = String(frame.id, HEX) + ": ";
      can_frame += String(frame.len) + ": ";
      can_frame += String(frame.data[0], DEC) + ", ";
      can_frame += String(frame.data[1], DEC) + ", ";
      can_frame += String(frame.data[2], DEC) + ", ";
      can_frame += String(frame.data[3], DEC) + ", ";
      can_frame += String(frame.data[4], DEC) + ", ";
      can_frame += String(frame.data[5], DEC) + ", ";
      can_frame += String(frame.data[6], DEC) + ", ";
      can_frame += String(frame.data[7], DEC) + ";";
      DEBUG_PRINTLN(can_frame);
      gReceivedFrameCount += 1 ;



      switch ( frame.id ) {

        // Header
        case DISPLAY_ADDR:
            recv_id = frame.data[0];
            recv_display = frame.data[1];
            recv_type = frame.data[2];

            break;
        // Value name part 1
        case DISPLAY_ADDR + 0x01:
            recv_name1[0] = frame.data[0];
            recv_name1[1] = frame.data[1];
            recv_name1[2] = frame.data[2];
            recv_name1[3] = frame.data[3];
            recv_name1[4] = frame.data[4];
            recv_name1[5] = frame.data[5];
            recv_name1[6] = frame.data[6];
            recv_name1[7] = frame.data[7];
            break;

        // Value name part 2
        case DISPLAY_ADDR + 0x02:
            recv_name2[0] = frame.data[0];
            recv_name2[1] = frame.data[1];
            recv_name2[2] = frame.data[2];
            recv_name2[3] = frame.data[3];
            recv_name2[4] = frame.data[4];
            recv_name2[5] = frame.data[5];
            recv_name2[6] = frame.data[6];
            recv_name2[7] = frame.data[7];
            break;

        // Value as String
        case DISPLAY_ADDR + 0x03:
            recv_value[0] = frame.data[0];
            recv_value[1] = frame.data[1];
            recv_value[2] = frame.data[2];
            recv_value[3] = frame.data[3];
            recv_value[4] = frame.data[4];
            recv_value[5] = frame.data[5];
            recv_value[6] = frame.data[6];
            recv_value[7] = frame.data[7];
            
            break;

        // Footer
        // This is an empty frame to initiate the processing
        case DISPLAY_ADDR + 0x0E:
            DEBUG_PRINTLN("ID:        " + String(recv_id));
            DEBUG_PRINTLN("DISPLAY:   " + String(recv_display));
            DEBUG_PRINTLN("VALUE TYP: " + String(recv_type));
            DEBUG_PRINTLN("NAME:      " + String(recv_name1) + String(recv_name2));
            //DEBUG_PRINT(recv_name2);
            //DEBUG_PRINT("VALUE:     " + String(recv_value) + " (" + String(strlen(recv_value)) + ")");
            strcpy(can_value_name1, recv_name1);
            strcpy(can_value_name2, recv_name2);
            strcpy(can_value, recv_value);
            switch (recv_type) {
                case 1: strcpy(can_value_type, "km/h"); break;
                case 2: strcpy(can_value_type, "\xb0 C"); break;
                case 3: strcpy(can_value_type, "bar"); break;
                case 4: strcpy(can_value_type, "V"); break;
                case 5: strcpy(can_value_type, "l"); break;
                case 6: strcpy(can_value_type, "U/min"); break;
                case 7: strcpy(can_value_type, "m"); break;
                case 8: strcpy(can_value_type, "km"); break;
                case 9: strcpy(can_value_type, "min"); break;
                case 10: strcpy(can_value_type, "sec"); break;
                case 11: strcpy(can_value_type, "l/min"); break;
                default: strcpy(can_value_type, "nan"); break;

            }
            DEBUG_PRINTLN("VALUE:     " + String(recv_value) + " " + String(value_type));



            strcpy(recv_name1, "00000000");
            strcpy(recv_name2, "00000000");

            break;

        // default for unknown frames
        default:
            can_frame = String(frame.id, HEX) + ": ";
            can_frame += String(frame.len) + ": ";
            can_frame += String(frame.data[0], DEC) + ", ";
            can_frame += String(frame.data[1], DEC) + ", ";
            can_frame += String(frame.data[2], DEC) + ", ";
            can_frame += String(frame.data[3], DEC) + ", ";
            can_frame += String(frame.data[4], DEC) + ", ";
            can_frame += String(frame.data[5], DEC) + ", ";
            can_frame += String(frame.data[6], DEC) + ", ";
            can_frame += String(frame.data[7], DEC) + ";";
            DEBUG_PRINTLN(can_frame);
            break;
            
    }
    }
  }
}

//——————————————————————————————————————————————————————————————————————————————

#else
void can_init() {}
void can_loop () {}
#endif //CANBUS