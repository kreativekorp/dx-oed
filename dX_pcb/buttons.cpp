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
	switch (PINB & 0x1A) {
		case 0x18: return 1; break;
		case 0x12: return 2; break;
		case 0x0A: return 3; break;
	}
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