#include "menu.h"
#include "display.h"
#include "fonts.h"
#include "settings.h"
#include "special.h"
#include <Arduino.h>
#include <avr/pgmspace.h>

static unsigned char dice_types[2][4] PROGMEM = {
	{F_P, F_N, F_F, F_S},
	{F_I, F_U, F_G, F_P},
};

static unsigned char menu_position = 0;

unsigned char in_menu(void) {
	return menu_position;
}

void menu_display(void) {
	switch (menu_position) {
		case 0:
			display_clear();
			break;
		case 1:
			display_char_4x4(
				F_T, F_Y,
				pgm_read_byte(&(dice_types[0][settings_dice_type])),
				pgm_read_byte(&(dice_types[1][settings_dice_type]))
			);
			break;
		case 2:
			switch (settings_dice_type) {
				case S_DICE_TYPE_PIPS:
					display_char_4x4(
						F_S, F_T,
						settings_pip_type ? F_E : F_W, F_N
					);
					break;
				case S_DICE_TYPE_NUMERIC:
					display_char_4x4(
						F_S, F_T,
						settings_digit_type ? F_7 : F_N,
						settings_digit_type ? F_S : F_O
					);
					break;
				case S_DICE_TYPE_FUDGE:
					display_number_bottom(F_S, F_T, settings_fudge_type);
					break;
				case S_DICE_TYPE_SPECIAL:
					display_char_4x4(
						F_S, F_T,
						get_special_dice_info(settings_special_type, SPECIAL_DICE_CHAR_0),
						get_special_dice_info(settings_special_type, SPECIAL_DICE_CHAR_1)
					);
					break;
			}
			break;
		case 3:
			display_number_bottom(F_M, F_N, settings_dice_type ? settings_num_min : settings_pip_min);
			break;
		case 4:
			display_number_bottom(F_M, F_X, settings_dice_type ? settings_num_max : settings_pip_max);
			break;
		case 5:
			display_number_bottom(F_B, F_R, settings_brightness);
			break;
		case 6:
			display_number_bottom(F_S, F_L, settings_sleep_time);
			break;
	}
}

void menu_advance(void) {
	menu_position++;
	if (settings_dice_type > 1 && menu_position > 2 && menu_position < 5) {
		menu_position = 5;
	} else if (menu_position > 6) {
		menu_position = 0;
	}
}

void menu_increment(void) {
	switch (menu_position) {
		case 1:
			settings_dice_type = (settings_dice_type + 1) & 0x3;
			break;
		case 2:
			switch (settings_dice_type) {
				case S_DICE_TYPE_PIPS:
					settings_pip_type ^= 1;
					break;
				case S_DICE_TYPE_NUMERIC:
					settings_digit_type ^= 1;
					break;
				case S_DICE_TYPE_FUDGE:
					settings_fudge_type++;
					if (settings_fudge_type > 3) {
						settings_fudge_type = 1;
					}
					break;
				case S_DICE_TYPE_SPECIAL:
					settings_special_type++;
					if (settings_special_type >= SPECIAL_DICE_COUNT) {
						settings_special_type = 0;
					}
					break;
			}
			break;
		case 3:
			if (settings_dice_type) {
				if (settings_num_min < settings_num_max) {
					settings_num_min++;
				}
			} else {
				if (settings_pip_min < settings_pip_max) {
					settings_pip_min++;
				}
			}
			break;
		case 4:
			if (settings_dice_type) {
				if (settings_num_max < S_NUM_MAX) {
					settings_num_max++;
				}
			} else {
				if (settings_pip_max < S_PIP_MAX) {
					settings_pip_max++;
				}
			}
			break;
		case 5:
			if (settings_brightness < S_BRIGHTNESS_MAX) {
				settings_brightness++;
				display_brightness(settings_brightness);
			}
			break;
		case 6:
			if (settings_sleep_time < S_SLEEP_TIME_MAX) {
				settings_sleep_time++;
			}
			break;
	}
}

void menu_decrement(void) {
	switch (menu_position) {
		case 1:
			settings_dice_type = (settings_dice_type - 1) & 0x3;
			break;
		case 2:
			switch (settings_dice_type) {
				case S_DICE_TYPE_PIPS:
					settings_pip_type ^= 1;
					break;
				case S_DICE_TYPE_NUMERIC:
					settings_digit_type ^= 1;
					break;
				case S_DICE_TYPE_FUDGE:
					settings_fudge_type--;
					if (settings_fudge_type < 1) {
						settings_fudge_type = 3;
					}
					break;
				case S_DICE_TYPE_SPECIAL:
					if (settings_special_type <= 0) {
						settings_special_type = SPECIAL_DICE_COUNT;
					}
					settings_special_type--;
					break;
			}
			break;
		case 3:
			if (settings_dice_type) {
				if (settings_num_min > S_NUM_MIN) {
					settings_num_min--;
				}
			} else {
				if (settings_pip_min > S_PIP_MIN) {
					settings_pip_min--;
				}
			}
			break;
		case 4:
			if (settings_dice_type) {
				if (settings_num_max > settings_num_min) {
					settings_num_max--;
				}
			} else {
				if (settings_pip_max > settings_pip_min) {
					settings_pip_max--;
				}
			}
			break;
		case 5:
			if (settings_brightness > S_BRIGHTNESS_MIN) {
				settings_brightness--;
				display_brightness(settings_brightness);
			}
			break;
		case 6:
			if (settings_sleep_time > S_SLEEP_TIME_MIN) {
				settings_sleep_time--;
			}
			break;
	}
}

void menu_exit(void) {
	menu_position = 0;
}