//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515 Demo in loopback mode
//——————————————————————————————————————————————————————————————————————————————
#include "hardware.h"

#ifdef CANBUS
#include <ACAN2515.h>
#include "canbus.h"
#include "canvalues.h"

//#define DISPLAY_ADDR 0xF0
#define DISPLAY_ADDR 0x6F0

CANMessage frame;
bool ok = false;

uint32_t gReceivedFrameCount = 0 ;
uint32_t gSentFrameCount = 0 ;

uint16_t ii = 0;
uint16_t req_addr = 0x12;
uint16_t display_req_addr = 0x00;
bool display_data_valid = false;
byte display_msg_type = 0;
byte display_frame_type = 0;
boolean available_values[2048];
uint16_t available_values2[256];
char display_desc[18];
byte display_data_type = 0;
char display_value1[9];
char display_value1_suffix[5];
char display_value2[9];
char display_value2_suffix[9];
bool wait_for_new_value = true;

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




static void receive0 (const CANMessage & inMessage) {
    //Serial.println ("Receive 0") ;
    //DEBUG_PRINT( "receive0 : 0x" + String(inMessage.id, HEX));
    read(inMessage);
}

static void canISR () {
    //DEBUG_PRINT(F("*"));
    //digitalWrite(DISPLAY_CS, HIGH);
    if ( !digitalRead(DISPLAY_CS) ) {
        //DEBUG_PRINT("SPI BUS is used for Display. Disable Diplay...")
        digitalWrite(DISPLAY_CS, HIGH);
    }
    /*else {
        DEBUG_PRINT("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ")
    }*/
    can.isr();
    //can.dispatchReceivedMessage();
    //while (can.dispatchReceivedMessage ()) { }
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
        /*while (!Serial) {
                delay (50) ;
                //digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
        }*/
        //--- Begin SPI
        SPI.begin () ;
        //--- Configure ACAN2515
        DEBUG_PRINT("Configure ACAN2515") ;
        ACAN2515Settings settings (QUARTZ_FREQUENCY, 50UL * 1000UL) ; // CAN bit rate 50 kb/s
        //settings.mRequestedMode = ACAN2515Settings::LoopBackMode ; // Select loopback mode
        settings.mReceiveBufferSize = 64 ;

        
        const ACAN2515Mask rxm0 = standard2515Mask (0x7F0, 0, 0) ;
        const ACAN2515AcceptanceFilter filter [] = {
                                standard2515Filter (DISPLAY_ADDR, 0, 0), receive0}; // RXF0 };
        

        //const uint16_t errorCode = can.begin (settings, [] { can.isr () ; }) ;
        const uint16_t errorCode = can.begin (settings,
                                                                        canISR,
                                                                        rxm0, // Value set to RXM0 register
                                                                        filter, // The filter array
                                                                        1) ; // Filter array size
        //const uint32_t errorCode = can.begin (settings, [] { can.isr () ; }, rxm0, filter, 1) ;
        if (errorCode == 0) {
                /*
                DEBUG_PRINT ("Bit Rate prescaler:  " + String(settings.mBitRatePrescaler)) ;
                DEBUG_PRINT ("Propagation Segment: " + String(settings.mPropagationSegment)) ;
                DEBUG_PRINT ("Phase Segment 1:     " + String(settings.mPhaseSegment1)) ;
                DEBUG_PRINT ("Phase Segment 2:     " + String(settings.mPhaseSegment2)) ;
                DEBUG_PRINT ("SJW:                 " + String(settings.mSJW)) ;
                DEBUG_PRINT ("Triple Sampling:     " + String(settings.mTripleSampling ? "yes" : "no")) ;
                DEBUG_PRINT ("Actual bit rate:     " + String(settings.actualBitRate()) + " bit/s") ;
                DEBUG_PRINT ("Exact bit rate ?     " + String(settings.exactBitRate () ? "yes" : "no")) ;
                DEBUG_PRINT ("Distance             " + String(settings.ppmFromDesiredBitRate()) + " ppm") ;
                DEBUG_PRINT ("Sample point:        " + String(settings.samplePointFromBitStart()) + "%") ;
                */
                DEBUG_PRINT ("Configuration OK!");
        }else{
                //Serial.print ("Configuration error 0x") ;
                //Serial.println (errorCode, HEX) ;
                DEBUG_PRINT ("Configuration error 0x" + String(errorCode, HEX)) ;
        }

        //request_display_description(0x12);
        display_data_valid = false;
}

void can_loop() {
    while (can.dispatchReceivedMessage ()) { }
}

static void read(CANMessage frame) {
    //DEBUG_PRINT ("Receive 0" + String(frame.id, HEX)) ;
    /*DEBUG_PRINT("0x" + String(frame.id, HEX) + ": " \
                            + String(frame.len) + ": " \
                            + String(frame.data[0], HEX) + ", " \
                            + String(frame.data[1], HEX) + ", " \
                            + String(frame.data[2], HEX) + ", " \
                            + String(frame.data[3], HEX) + ", " \
                            + String(frame.data[4], HEX) + ", " \
                            + String(frame.data[5], HEX) + ", " \
                            + String(frame.data[6], HEX) + ", " \
                            + String(frame.data[7], HEX) + ";" \
                            );*/

    switch ( frame.id ) {
        case DISPLAY_ADDR + 0x01:
            // receive a reply for a desplay request
            DEBUG_PRINT("receive display description for 0x" + String(frame.data16[0], HEX));
            if ( frame.data16[0] == display_req_addr ) {
                display_msg_type = frame.data[2];
                display_frame_type = frame.data[3];
                display_data_valid = true;
                wait_for_new_value = false;
                DEBUG_PRINT("display type : " + String(display_msg_type, DEC));
                DEBUG_PRINT("display requested is valid");
            }
            else {
                display_data_valid = false;
                DEBUG_PRINT("DISPLAY DATA NOT VALID...");
            }
            break;
        case DISPLAY_ADDR + 0x02:
            // receive a description part 1
            if ( display_data_valid ) {
                for ( ii = 0; ii < 8; ii++ ) {
                    display_desc[ii] = frame.data[ii];
                }
            }
            break;
        case DISPLAY_ADDR + 0x03:
            // receive a description part 2
            if ( display_data_valid ) {
                for ( ii = 0; ii < 8; ii++ ) {
                    display_desc[ii+8] = frame.data[ii];
                }
            }
            //DEBUG_PRINT("DISPLAY DESC : " + String(display_desc));
            DEBUG_PRINT("Receive description : " + String(display_desc));
            break;
        case DISPLAY_ADDR + 0x04:
            // receive the value types as a string
            if ( display_data_valid ) {
                for ( ii = 0; ii < 4; ii++ ) {
                    display_value1_suffix[ii] = frame.data[ii];
                }
                for ( ii = 0; ii < 4; ii++ ) {
                    display_value2_suffix[ii] = frame.data[ii+4];
                }

                /*if ( strcmp(display_value1_suffix, "°C") == 0) {
                    DEBUG_PRINT("Convert °C");
                    strcpy(display_value1_suffix, "\xb0 C");
                }*/
            }
            DEBUG_PRINT("Receive suffix : " + String(display_value1_suffix));
            break;
        case DISPLAY_ADDR + 0x05:
            // receive the 1st value as a string
            if ( display_data_valid and !wait_for_new_value ) {
                for ( ii = 0; ii < 8; ii++ ) {
                    display_value1[ii] = frame.data[ii];
                }
            }
            //DEBUG_PRINT("DISPLAY Value 1 : " + String(display_value1) + " " + String(display_value1_suffix));
            break;
        
        case DISPLAY_ADDR + 0x06:
            // receive the 2nd value as a string
            if ( display_data_valid and !wait_for_new_value ) {
                for ( ii = 0; ii < 8; ii++ ) {
                    display_value2[ii] = frame.data[ii];
                }
            }
            //DEBUG_PRINT("DISPLAY Value 2 : " + String(display_value2) + " " + String(display_value2_suffix));
            break;
        case DISPLAY_ADDR + 0x0f:
            /*if ( !available_values[frame.data16[0]] ) {
                DEBUG_PRINT("register available field: 0x" + String(frame.data16[0], HEX));
            }
            available_values[frame.data16[0]] = true;
            */

            //DEBUG_PRINT("ADDR: 0x" + String(frame.data16[0], HEX));
            byte high = frame.data16[0] >> 4;
            byte low = frame.data16[0] - (high << 4);
            //DEBUG_PRINT("HIGH: 0x" + String(high, HEX));
            //DEBUG_PRINT("LOW : 0x" + String(low, HEX));
            //DEBUG_PRINT("READ: " + String(bitRead(available_values2[high], low )));
            if ( !bitRead(available_values2[high], low) ) {
                //DEBUG_PRINT("HIGH: 0x" + String(high, HEX));
                //DEBUG_PRINT("LOW : 0x" + String(low, HEX));
                //DEBUG_PRINT("READ: " + String(bitRead(available_values2[high], low )));
                bitSet(available_values2[high], low);
                DEBUG_PRINT("register available field: 0x" + String(frame.data16[0], HEX));
            }
            
            break;
            /*for ( ii = 0; ii < sizeof(available_values); ii++ ) {
                if ( available_values[ii] == 0 ) {
                    available_values[ii] = frame.data[0];
                    DEBUG_PRINT("register available field: 0x" + String(frame.data[0], HEX));
                    break;
                }
                else if ( available_values[ii] == frame.data[0] ) {
                    //DEBUG_PRINT("field already rigistered: 0x" + String(frame.data[0], HEX));
                    break;
                }
            }*/
    }
}

void send(CANMessage can_frame) {
    ok = can.tryToSend (can_frame) ;
    if (ok) {
        gSentFrameCount += 1 ;
    }
    else {
        DEBUG_PRINT("Failed to send CAN Data 0x" + can_frame.id);
    }
}

void request_display_description(uint16_t value_addr) {
    DEBUG_PRINT("REQUEST : 0x" + String(value_addr, HEX));
    display_req_addr = value_addr;
    frame.id = DISPLAY_ADDR;
    frame.len = 2;
    frame.data16[0] = value_addr;
    send(frame);
    //display_data_valid = true;
    strcpy(display_desc, "waiting...");
    strcpy(display_value1, "nan");
    strcpy(display_value1_suffix, "nan");
    strcpy(display_value2, "nan");
    strcpy(display_value2_suffix, "nan");
    wait_for_new_value = true;
}

bool can_next() {
    DEBUG_PRINT("actual addr : 0x" + String(display_req_addr, HEX));

    /*for ( ii = display_req_addr + 1; ii < sizeof(available_values); ii++ ) {
        if ( available_values[ii] ) {
            DEBUG_PRINT("NEXT value...");
            request_display_description(ii);

            return true;
        }
    }*/

    byte high = display_req_addr >> 4;
    byte low = display_req_addr - (high << 4);
    for ( ii = low + 1; ii < 16; ii++) {
        if ( bitRead(available_values2[high], ii)) {
            DEBUG_PRINT("NEXT value...");
            request_display_description((high << 4) + ii);

            return true;
        }
    }
    //DEBUG_PRINT(String(sizeof(available_values2)/ sizeof(uint16_t), DEC));
    for ( byte i = high + 1; i < sizeof(available_values2) / sizeof(uint16_t) -1; i++) {
        DEBUG_PRINT(String(i, DEC));
        for ( ii = 0; ii < 16; ii++) {
            if ( bitRead(available_values2[i], ii)) {
                DEBUG_PRINT("NEXT value...");
                request_display_description((i << 4) + ii);

                return true;
            }
        }
    }
    DEBUG_PRINT("NO MORE values...");
    display_req_addr = 0x00;
    return false;

    /*if ( display_req_addr == 0x00 ) {
        if ( available_values[0] == 0x00 ) {
            DEBUG_PRINT("Array is empty...");
            display_req_addr = 0;
            return false;
        }
        else {
            DEBUG_PRINT("Switch to first...");
            request_display_description(available_values[0]);
            return true;
        }
        
    }
    else {
        for ( ii = 0; ii < sizeof(available_values); ii++) {
            DEBUG_PRINT("0x" + String(available_values[ii], HEX));
            if ( ii+1 == sizeof(available_values) ) {
                DEBUG_PRINT("End of array...");
                //request_display_description(available_values(0));
                display_req_addr = 0x00;
                return false;
            }
            if ( available_values[ii] == display_req_addr ) {
                if ( available_values[ii+1] == 0x00 ) {
                    DEBUG_PRINT("Last value...");
                    //display_req_addr = 0x00;
                    display_data_valid = false;
                    request_display_description(0x00);

                    return false;
                }
                else {
                    DEBUG_PRINT("NEXT value...");
                    request_display_description(available_values[ii+1]);

                    return true;
                }
                
            }
        }
    }*/
}


#else
void can_init() {}
void can_loop() {}
#endif //CANBUS