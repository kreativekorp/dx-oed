/*
 * This is the dX firmware for the custom PCB with piezo.
 * If you have the Adafruit Trinket, please use dX_trinket instead.
 * If you have the custom PCB with buttons, please use dX_pcb instead.
 */

#include "buttons.h"
#include "display.h"
#include "fonts.h"
#include "menu.h"
#include "roll.h"
#include "settings.h"
#include "special.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <TinyWireM.h>
#include <avr/pgmspace.h>
#include <avr/power.h>
#include <avr/sleep.h>

unsigned long last_event;

void setup() {
	/* System Initialization */
	DDRB  &=~ 0x1A; /* pinMode(1, INPUT); pinMode(3, INPUT); pinMode(4, INPUT); */
	PORTB &=~ 0x1A; /* digitalWrite(1, LOW); digitalWrite(3, LOW); digitalWrite(4, LOW); */
	randomSeed(millis() + analogRead(2) + analogRead(3));
	PCMSK |=  0x1A; /* PCMSK |= _BV(PCINT1); PCMSK |= _BV(PCINT3); PCMSK |= _BV(PCINT4); */
	power_timer1_disable();
	/* dX Initialization */
	display_setup();
	settings_read();
	menu_exit();
	buttons_init();
	display_char_4x8(F_d, F_X);
	last_event = millis();
}

void system_sleep() {
	/* dX Suspend */
	display_sleep();
	settings_write();
	menu_exit();
	buttons_init();
	/* System Suspend */
	GIMSK = _BV(PCIE);
	power_all_disable();
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sei();
	sleep_cpu();
	/* System Resume */
	sleep_disable();
	GIMSK = 0;
	power_timer0_enable();
	power_usi_enable();
	power_adc_enable();
	/* dX Resume */
	display_wake();
	settings_read();
	menu_exit();
	buttons_init();
	display_clear();
	last_event = millis();
}

void loop() {
	unsigned char e = get_button_event();
	if (e) {
		unsigned char en = e & BUTTON_EVENT_NUMBER;
		unsigned char et = e & BUTTON_EVENT_TYPE;
		switch (en) {
			case 1: /* MENU */
				switch (et) {
					case BUTTON_EVENT_TYPE_FIRST:
						menu_advance();
						menu_display();
						break;
					case BUTTON_EVENT_TYPE_REPEAT:
						menu_exit();
						menu_display();
						break;
				}
				break;
			case 2: /* ROLL - */
				if (in_menu()) {
					switch (et) {
						case BUTTON_EVENT_TYPE_FIRST:
						case BUTTON_EVENT_TYPE_REPEAT:
							menu_decrement();
							menu_display();
							break;
					}
				} else {
					roll();
				}
				break;
			case 3: /* SLEEP + */
				if (in_menu()) {
					switch (et) {
						case BUTTON_EVENT_TYPE_FIRST:
						case BUTTON_EVENT_TYPE_REPEAT:
							menu_increment();
							menu_display();
							break;
					}
				} else {
					switch (et) {
						case BUTTON_EVENT_TYPE_RELEASE:
							system_sleep();
							break;
					}
				}
				break;
		}
		last_event = millis();
	} else if (!in_menu()) {
		if (get_piezo_state()) {
			roll();
			last_event = millis();
		} else if (settings_sleep_time && ((millis() - last_event) / 1000) >= settings_sleep_time) {
			system_sleep();
		}
	}
}

ISR(PCINT0_vect) {}
ISR(PCINT1_vect) {}
ISR(PCINT2_vect) {}
ISR(PCINT3_vect) {}
ISR(PCINT4_vect) {}
ISR(PCINT5_vect) {}