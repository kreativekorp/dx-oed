#ifndef BUTTONS_H
#define BUTTONS_H

#define ANALOG_INPUT_BUTTONS 3
#define ANALOG_INPUT_PIEZO   2

#define THRESHOLD_BUTTON_MULTI 848
#define THRESHOLD_BUTTON_1     804
#define THRESHOLD_BUTTON_2     733
#define THRESHOLD_BUTTON_3     614
#define THRESHOLD_PIEZO        100

#define DEBOUNCE_TIME  20
#define REPEAT_DELAY  800
#define REPEAT_RATE   400

#define BUTTON_EVENT_NUMBER       0x0F
#define BUTTON_EVENT_TYPE         0xF0
#define BUTTON_EVENT_TYPE_DOWN    0x00
#define BUTTON_EVENT_TYPE_FIRST   0x10
#define BUTTON_EVENT_TYPE_REPEAT  0x20
#define BUTTON_EVENT_TYPE_RELEASE 0x30

void buttons_init(void);
unsigned char get_button_state(void);
unsigned char get_button_event(void);
unsigned char get_piezo_state(void);

#endif