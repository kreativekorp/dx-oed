#include "settings.h"
#include "display.h"
#include <Arduino.h>
#include <EEPROM.h>

unsigned char settings_valid = 0;
unsigned char settings_dice_type;
unsigned char settings_pip_type;
unsigned char settings_digit_type;
unsigned char settings_fudge_type;
unsigned char settings_special_type;
unsigned char settings_pip_min;
unsigned char settings_pip_max;
unsigned char settings_num_min;
unsigned char settings_num_max;
unsigned char settings_brightness;
unsigned char settings_sleep_time;

void settings_reset(void) {
	settings_valid        = S_SETTINGS_VALID;
	settings_dice_type    = S_DICE_TYPE_PIPS;
	settings_pip_type     = 0;
	settings_digit_type   = 0;
	settings_fudge_type   = 2;
	settings_special_type = 0;
	settings_pip_min      = 1;
	settings_pip_max      = 6;
	settings_num_min      = 1;
	settings_num_max      = 20;
	settings_brightness   = DISPLAY_BRIGHTNESS;
	settings_sleep_time   = 10;
	display_brightness(settings_brightness);
}

void settings_read(void) {
	if (EEPROM.read(0) == S_SETTINGS_VALID) {
		settings_valid        = S_SETTINGS_VALID;
		settings_dice_type    = EEPROM.read(1);
		settings_pip_type     = EEPROM.read(2);
		settings_digit_type   = EEPROM.read(3);
		settings_fudge_type   = EEPROM.read(4);
		settings_special_type = EEPROM.read(5);
		settings_pip_min      = EEPROM.read(6);
		settings_pip_max      = EEPROM.read(7);
		settings_num_min      = EEPROM.read(8);
		settings_num_max      = EEPROM.read(9);
		settings_brightness   = EEPROM.read(10);
		settings_sleep_time   = EEPROM.read(11);
		display_brightness(settings_brightness);
	} else {
		settings_reset();
	}
}

static void settings_eeprom_write(int address, unsigned char value) {
	if (EEPROM.read(address) != value) {
		EEPROM.write(address, value);
	}
}

void settings_write(void) {
	if (settings_valid == S_SETTINGS_VALID) {
		settings_eeprom_write(0,  S_SETTINGS_VALID);
		settings_eeprom_write(1,  settings_dice_type);
		settings_eeprom_write(2,  settings_pip_type);
		settings_eeprom_write(3,  settings_digit_type);
		settings_eeprom_write(4,  settings_fudge_type);
		settings_eeprom_write(5,  settings_special_type);
		settings_eeprom_write(6,  settings_pip_min);
		settings_eeprom_write(7,  settings_pip_max);
		settings_eeprom_write(8,  settings_num_min);
		settings_eeprom_write(9,  settings_num_max);
		settings_eeprom_write(10, settings_brightness);
		settings_eeprom_write(11, settings_sleep_time);
	}
}