#include "buttons.h"
#include <Arduino.h>

static unsigned char button_state;
static unsigned char button_phase;
static unsigned long button_time;

void buttons_init(void) {
	button_state = 0;
	button_phase = 0;
	button_time = 0;
}

unsigned char get_button_state(void) {
	int a = analogRead(ANALOG_INPUT_BUTTONS);
	if (a > THRESHOLD_BUTTON_MULTI) return 0;
	if (a > THRESHOLD_BUTTON_1) return 1;
	if (a > THRESHOLD_BUTTON_2) return 2;
	if (a > THRESHOLD_BUTTON_3) return 3;
	return 0;
}

unsigned char get_button_event(void) {
	unsigned char s = get_button_state();
	if (s && (s == button_state)) {
		unsigned long t = (millis() - button_time);
		switch (button_phase) {
			case 1:
				if (t >= DEBOUNCE_TIME) {
					button_phase = 2;
					button_time = millis();
					return s | BUTTON_EVENT_TYPE_FIRST;
				} else {
					return 0;
				}
				break;
			case 2:
				if (t >= REPEAT_DELAY) {
					button_phase = 3;
					button_time = millis();
					return s | BUTTON_EVENT_TYPE_REPEAT;
				} else {
					return s | BUTTON_EVENT_TYPE_DOWN;
				}
				break;
			case 3:
				if (t >= REPEAT_RATE) {
					button_time = millis();
					return s | BUTTON_EVENT_TYPE_REPEAT;
				} else {
					return s | BUTTON_EVENT_TYPE_DOWN;
				}
				break;
		}
	} else {
		unsigned char re = (button_phase > 1) ? (button_state | BUTTON_EVENT_TYPE_RELEASE) : 0;
		button_state = s;
		button_phase = s ? 1 : 0;
		button_time = s ? millis() : 0;
		return re;
	}
}

unsigned char get_piezo_state(void) {
	return (analogRead(ANALOG_INPUT_PIEZO) > THRESHOLD_PIEZO);
}