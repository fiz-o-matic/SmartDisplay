/****************************************************
 * fiz-o-matic
 * https://fiz-o-matic.net/
 *
 * fiz-o-matic Smart Cockpit
 *
 * Author: Brun
 * License: Creative Common (CC BY-NC-SA 4.0)
 ****************************************************/

#include "canbus.h"
//#include "hardware.h"

#ifdef CANBUS

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
char value_type[6];

void can_init() {
  CAN.setPins(CAN_CS, CAN_IRQ);
  // start the CAN bus at 50 kbps
  DEBUG_PRINTLN(F("CAN Start"));

  if (CAN.begin(50E3)) {
    DEBUG_PRINTLN(F("CAN Initialized "));
    CAN.onReceive(can_receive);
    can_active = true;
    CAN.filter(0x80);
    CAN.filter(0x80, 0x7F0);
  }
  else {
    DEBUG_PRINTLN(F("CAN FAILED"));
    while(1) {
      delay(2000);
    }
  }
}


void can_loop () {

  // return if timer is not reached
  if ( !timer_check(&canbus_timer, CANBUS_TIMER) ) return;

  //can_send();

}



void can_receive(int packetSize) {
  String msg;
  can_id = CAN.packetId();

  // received a packet
  DEBUG_PRINT(F("CAN: "));

  //msg = F("0x");
  //msg += String(can_id, HEX);
  //msg += F(": ");
  DEBUG_PRINT(String(can_id, HEX));
  DEBUG_PRINT(F(": "));

  if (CAN.packetRtr()) {
    Serial.print(" and requested length ");
    DEBUG_PRINT(CAN.packetDlc());
  } else {
    // only print packet data for non-RTR packets

    field_cnt = 0;
    for ( byte i=0; i>=7; i++ ) {
      can_buff[i] = 0;
    }
    while (CAN.available()) {
      //Serial.print((char)CAN.read());
      //DEBUG_PRINT(String(CAN.read(), DEC));
      can_buff[field_cnt] = CAN.read();
      DEBUG_PRINT(String(can_buff[field_cnt], DEC));
      DEBUG_PRINT(F(","));

      //msg += String(can_buff[field_cnt], DEC);
      //msg += F(",");
      field_cnt++;
    }
    DEBUG_PRINTLN(F(";"));

    switch ( can_id ) {

    // Header
    case DISPLAY_ADDR:
        recv_id = can_buff[0];
        recv_display = can_buff[1];
        recv_type = can_buff[2];

        break;
    // Value name part 1
    case DISPLAY_ADDR + 0x01:
        recv_name1[0] = can_buff[0];
        recv_name1[1] = can_buff[1];
        recv_name1[2] = can_buff[2];
        recv_name1[3] = can_buff[3];
        recv_name1[4] = can_buff[4];
        recv_name1[5] = can_buff[5];
        recv_name1[6] = can_buff[6];
        recv_name1[7] = can_buff[7];
        break;

    // Value name part 2
    case DISPLAY_ADDR + 0x02:
        recv_name2[0] = can_buff[0];
        recv_name2[1] = can_buff[1];
        recv_name2[2] = can_buff[2];
        recv_name2[3] = can_buff[3];
        recv_name2[4] = can_buff[4];
        recv_name2[5] = can_buff[5];
        recv_name2[6] = can_buff[6];
        recv_name2[7] = can_buff[7];
        break;

    // Value as String
    case DISPLAY_ADDR + 0x03:
        recv_value[0] = can_buff[0];
        recv_value[1] = can_buff[1];
        recv_value[2] = can_buff[2];
        recv_value[3] = can_buff[3];
        recv_value[4] = can_buff[4];
        recv_value[5] = can_buff[5];
        recv_value[6] = can_buff[6];
        recv_value[7] = can_buff[7];

        break;

    // Footer
    // This is an empty frame to initiate the processing
    case DISPLAY_ADDR + 0x0E:
        DEBUG_PRINTLN("ID:        " + String(recv_id));
        DEBUG_PRINTLN("DISPLAY:   " + String(recv_display));
        DEBUG_PRINTLN("VALUE TYP: " + String(recv_type));
        DEBUG_PRINTLN("NAME:      " + String(recv_name1) + String(recv_name2));
        //DEBUG_PRINTLN(recv_name2);
        //DEBUG_PRINTLN("VALUE:     " + String(recv_value) + " (" + String(strlen(recv_value)) + ")");
        switch (recv_type) {
            case 1: strcpy(value_type, "km/h"); break;
            case 2: strcpy(value_type, "°C"); break;
            case 3: strcpy(value_type, "bar"); break;
            case 4: strcpy(value_type, "V"); break;
            case 5: strcpy(value_type, "l"); break;
            case 6: strcpy(value_type, "U/min"); break;
            case 7: strcpy(value_type, "m"); break;
            case 8: strcpy(value_type, "km"); break;
            case 9: strcpy(value_type, "min"); break;
            case 10: strcpy(value_type, "sec"); break;
            case 11: strcpy(value_type, "l/min"); break;
            default: strcpy(value_type, "nan"); break;

        }
        DEBUG_PRINTLN("VALUE:     " + String(recv_value) + " " + String(value_type));



        strcpy(recv_name1, "00000000");
        strcpy(recv_name2, "00000000");
        break;

    // default for unknown frames
    default:
        /*can_frame = String(can_id, HEX) + ": ";
        can_frame += String(field_cnt) + ": ";
        can_frame += String(can_buff[0], DEC) + ", ";
        can_frame += String(can_buff[1], DEC) + ", ";
        can_frame += String(can_buff[2], DEC) + ", ";
        can_frame += String(can_buff[3], DEC) + ", ";
        can_frame += String(can_buff[4], DEC) + ", ";
        can_frame += String(can_buff[5], DEC) + ", ";
        can_frame += String(can_buff[6], DEC) + ", ";
        can_frame += String(can_buff[7], DEC) + ";";*/
        //DEBUG_PRINT(can_frame);
        break;
        
    } 


  }
}

#else
void can_init() {}
void can_loop () {}
#endif //CANBUS
