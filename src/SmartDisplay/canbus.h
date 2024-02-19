#ifndef CAN_H
#define CAN_H

#include <Arduino.h>
#include "hardware.h"

void can_init();
void can_loop();
static void read(CANMessage frame);
void send(CANMessage can_frame);
void request_display_description(uint16_t value_addr);


//CAN canbus = CAN();

class CAN {
    private:
        
    public:
        //CAN();
        //void can_loop();
        //void hase();

        void setup() {
            DEBUG_PRINT("CAN Setup...");
            can_init();
            
        }

        void loop() {
            DEBUG_PRINT("CAN Loop...");
            can_loop();
            
        }

        

    

}CAN;


#endif