#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_ADDR       0x70
#define DISPLAY_BRIGHTNESS    7

void display_cmd(unsigned char cmd);
void display_brightness(unsigned char brightness);
void display_clear(void);
void display_setup(void);
void display_sleep(void);
void display_wake(void);

void display_char_8x8(unsigned char ch);
void display_char_4x8(unsigned char ch0, unsigned char ch1);
void display_char_2x8(unsigned char ch0, unsigned char ch1, unsigned char ch2);
void display_char_4x4(unsigned char ch0, unsigned char ch1, unsigned char ch2, unsigned char ch3);
void display_char_2x4(unsigned char ch0, unsigned char ch1, unsigned char ch2, unsigned char ch3, unsigned char ch4);
void display_chars(unsigned char ch0, unsigned char ch1);
void display_number(unsigned char i);
void display_number_alt(unsigned char i);
void display_number_bottom(unsigned char ch0, unsigned char ch1, unsigned char i);
void display_pips(unsigned char i);
void display_pips_alt(unsigned char i);

#endif