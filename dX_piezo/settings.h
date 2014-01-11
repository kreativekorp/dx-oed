#ifndef SETTINGS_H
#define SETTINGS_H

#define S_SETTINGS_VALID  0x2B

#define S_DICE_TYPE_PIPS     0
#define S_DICE_TYPE_NUMERIC  1
#define S_DICE_TYPE_FUDGE    2
#define S_DICE_TYPE_SPECIAL  3

#define S_PIP_MIN  0
#define S_PIP_MAX  25

#define S_NUM_MIN  0
#define S_NUM_MAX  180

#define S_BRIGHTNESS_MIN  1
#define S_BRIGHTNESS_MAX  15

#define S_SLEEP_TIME_MIN  0
#define S_SLEEP_TIME_MAX  180

extern unsigned char settings_valid;
extern unsigned char settings_dice_type;
extern unsigned char settings_pip_type;
extern unsigned char settings_digit_type;
extern unsigned char settings_fudge_type;
extern unsigned char settings_special_type;
extern unsigned char settings_pip_min;
extern unsigned char settings_pip_max;
extern unsigned char settings_num_min;
extern unsigned char settings_num_max;
extern unsigned char settings_brightness;
extern unsigned char settings_sleep_time;

void settings_reset(void);
void settings_read(void);
void settings_write(void);

#endif