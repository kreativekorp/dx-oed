#include "display.h"
#include "fonts.h"
#include <Arduino.h>
#include <TinyWireM.h>

static unsigned char display_buf[8];

void display_cmd(unsigned char cmd) {
	TinyWireM.beginTransmission(DISPLAY_ADDR);
	TinyWireM.write(cmd);
	TinyWireM.endTransmission();
}

void display_brightness(unsigned char brightness) {
	display_cmd(0xE0 | (brightness & 0x0F));
}

void display_clear(void) {
	unsigned char i;
	TinyWireM.beginTransmission(DISPLAY_ADDR);
	for (i = 0; i < 17; i++) {
		TinyWireM.write(0);
	}
	TinyWireM.endTransmission();
}

void display_setup(void) {
	TinyWireM.begin();
	display_clear();
	display_cmd(0x21);
	display_brightness(DISPLAY_BRIGHTNESS);
	display_cmd(0x81);
}

void display_sleep(void) {
	display_cmd(0x20);
}

void display_wake(void) {
	TinyWireM.begin();
	display_clear();
	display_cmd(0x21);
}

static void display_buffer(void) {
	unsigned char i;
	TinyWireM.beginTransmission(DISPLAY_ADDR);
	TinyWireM.write(0);
	for (i = 0; i < 8; i++) {
		TinyWireM.write(display_buf[i]);
		TinyWireM.write(0);
	}
	TinyWireM.endTransmission();
}

void display_char_8x8(unsigned char ch) {
	display_buf[7] = 0;
	display_buf[6] = get_font_column_8x8(ch, 0);
	display_buf[5] = get_font_column_8x8(ch, 1);
	display_buf[4] = get_font_column_8x8(ch, 2);
	display_buf[3] = get_font_column_8x8(ch, 3);
	display_buf[2] = get_font_column_8x8(ch, 4);
	display_buf[1] = get_font_column_8x8(ch, 5);
	display_buf[0] = get_font_column_8x8(ch, 6);
	display_buffer();
}

void display_char_4x8(unsigned char ch0, unsigned char ch1) {
	display_buf[7] = 0;
	display_buf[6] = get_font_column_4x8(ch0, 0);
	display_buf[5] = get_font_column_4x8(ch0, 1);
	display_buf[4] = get_font_column_4x8(ch0, 2);
	display_buf[3] = 0;
	display_buf[2] = get_font_column_4x8(ch1, 0);
	display_buf[1] = get_font_column_4x8(ch1, 1);
	display_buf[0] = get_font_column_4x8(ch1, 2);
	display_buffer();
}

void display_char_2x8(unsigned char ch0, unsigned char ch1, unsigned char ch2) {
	display_buf[7] = get_font_column_2x8(ch0, 0);
	display_buf[6] = get_font_column_2x8(ch0, 1);
	display_buf[5] = 0;
	display_buf[4] = get_font_column_2x8(ch1, 0);
	display_buf[3] = get_font_column_2x8(ch1, 1);
	display_buf[2] = 0;
	display_buf[1] = get_font_column_2x8(ch2, 0);
	display_buf[0] = get_font_column_2x8(ch2, 1);
	display_buffer();
}

void display_char_4x4(unsigned char ch0, unsigned char ch1, unsigned char ch2, unsigned char ch3) {
	display_buf[7] =                                      0                                     ;
	display_buf[6] = (get_font_column_4x4(ch0, 0) & 0x0F) | (get_font_column_4x4(ch2, 0) & 0xF0);
	display_buf[5] = (get_font_column_4x4(ch0, 1) & 0x0F) | (get_font_column_4x4(ch2, 1) & 0xF0);
	display_buf[4] = (get_font_column_4x4(ch0, 2) & 0x0F) | (get_font_column_4x4(ch2, 2) & 0xF0);
	display_buf[3] =                                      0                                     ;
	display_buf[2] = (get_font_column_4x4(ch1, 0) & 0x0F) | (get_font_column_4x4(ch3, 0) & 0xF0);
	display_buf[1] = (get_font_column_4x4(ch1, 1) & 0x0F) | (get_font_column_4x4(ch3, 1) & 0xF0);
	display_buf[0] = (get_font_column_4x4(ch1, 2) & 0x0F) | (get_font_column_4x4(ch3, 2) & 0xF0);
	display_buffer();
}

void display_char_2x4(unsigned char ch0, unsigned char ch1, unsigned char ch2, unsigned char ch3, unsigned char ch4) {
	display_buf[7] =                                        (get_font_column_2x4(ch2, 0) & 0xF0);
	display_buf[6] = (get_font_column_4x4(ch0, 0) & 0x0F) | (get_font_column_2x4(ch2, 1) & 0xF0);
	display_buf[5] = (get_font_column_4x4(ch0, 1) & 0x0F)                                       ;
	display_buf[4] = (get_font_column_4x4(ch0, 2) & 0x0F) | (get_font_column_2x4(ch3, 0) & 0xF0);
	display_buf[3] =                                        (get_font_column_2x4(ch3, 1) & 0xF0);
	display_buf[2] = (get_font_column_4x4(ch1, 0) & 0x0F)                                       ;
	display_buf[1] = (get_font_column_4x4(ch1, 1) & 0x0F) | (get_font_column_2x4(ch4, 0) & 0xF0);
	display_buf[0] = (get_font_column_4x4(ch1, 2) & 0x0F) | (get_font_column_2x4(ch4, 1) & 0xF0);
	display_buffer();
}

void display_chars(unsigned char ch0, unsigned char ch1) {
	if (ch0) {
		if (ch1) {
			display_char_4x8(ch0, ch1);
		} else {
			display_char_8x8(ch0);
		}
	} else {
		display_char_8x8(ch1);
	}
}

void display_number(unsigned char i) {
	if (i < 10) {
		display_char_8x8(F_DIGIT(i));
	} else if (i < 100) {
		display_char_4x8(F_DIGIT(i / 10), F_DIGIT(i % 10));
	} else {
		display_char_2x8(F_DIGIT(i / 100), F_DIGIT((i / 10) % 10), F_DIGIT(i % 10));
	}
}

void display_number_alt(unsigned char i) {
	if (i < 10) {
		display_char_8x8(F_DIGIT_ALT(i));
	} else if (i < 100) {
		display_char_4x8(F_DIGIT_ALT(i / 10), F_DIGIT_ALT(i % 10));
	} else {
		display_char_2x8(F_DIGIT_ALT(i / 100), F_DIGIT_ALT((i / 10) % 10), F_DIGIT_ALT(i % 10));
	}
}

void display_number_bottom(unsigned char ch0, unsigned char ch1, unsigned char i) {
	if (i < 10) {
		display_char_2x4(ch0, ch1, F_BLANK, F_BLANK, F_DIGIT(i));
	} else if (i < 100) {
		display_char_2x4(ch0, ch1, F_BLANK, F_DIGIT(i / 10), F_DIGIT(i % 10));
	} else {
		display_char_2x4(ch0, ch1, F_DIGIT(i / 100), F_DIGIT((i / 10) % 10), F_DIGIT(i % 10));
	}
}

void display_pips(unsigned char i) {
	display_char_8x8(F_PIP(i));
}

void display_pips_alt(unsigned char i) {
	display_char_8x8(F_PIP_ALT(i));
}