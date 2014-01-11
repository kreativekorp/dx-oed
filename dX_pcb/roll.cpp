#include "roll.h"
#include "display.h"
#include "fonts.h"
#include "settings.h"
#include "special.h"
#include <Arduino.h>

void roll(void) {
	unsigned char value;
	switch (settings_dice_type) {
		case S_DICE_TYPE_PIPS:
			value = random(settings_pip_min, settings_pip_max + 1);
			if (settings_pip_type) display_pips_alt(value);
			else                   display_pips(value);
			break;
		case S_DICE_TYPE_NUMERIC:
			value = random(settings_num_min, settings_num_max + 1);
			if (settings_digit_type) display_number_alt(value);
			else                     display_number(value);
			break;
		case S_DICE_TYPE_FUDGE:
			value = random(0, 6);
			if      (value <  settings_fudge_type      ) value = F_PLUS;
			else if (value < (settings_fudge_type << 1)) value = F_MINUS;
			else                                         value = F_BLANK;
			display_char_8x8(value);
			break;
		case S_DICE_TYPE_SPECIAL:
			value = random(0, get_special_dice_info(settings_special_type, SPECIAL_DICE_SIDES));
			display_special_dice(settings_special_type, value);
			break;
	}
}