
#define MSG_TYPE_UNVISABLE 1
#define MSG_TYPE_NORMAL 2
#define MSG_TYPE_WARNING 3
#define MSG_TYPE_CUSTOM 4
#define MSG_TYPE_STRING 5
#define MSG_TYPE_1VALUE 6
#define MSG_TYPE_2VALUES 8



extern uint16_t display_req_addr;
extern bool display_data_valid;
extern byte display_msg_type;

extern boolean available_values[2048];
extern uint16_t available_values2[];
extern char display_desc[18];
extern byte display_data_type;
extern char display_value1[9];
extern char display_value1_suffix[5];
extern char display_value2[9];
extern char display_value2_suffix[9];