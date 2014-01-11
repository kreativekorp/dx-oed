#include "special.h"
#include "display.h"
#include "fonts.h"
#include <Arduino.h>
#include <avr/pgmspace.h>

static unsigned char special_dice_info[SPECIAL_DICE_COUNT][5] PROGMEM = {
	/* twocc   h  addr  ln */
	{ F_Y,F_N, 0, 0x46,  2 }, /* YesNo */
	{ F_H,F_T, 0, 0x41,  2 }, /* Coin Flip */
	{ F_B,F_6, 0, 0x49,  6 }, /* Backgammon 6 */
	{ F_B,F_8, 0, 0x48,  8 }, /* Backgammon 8 */
	{ F_B,F_W, 0, 0x50,  6 }, /* Bowling */
	{ F_C,F_S, 0, 0x1C,  4 }, /* Card Suits */
	{ F_C,F_R, 0, 0x00, 13 }, /* Card Ranks */
	{ F_C,F_H, 0, 0x16,  6 }, /* Chess */
	{ F_C,F_M, 0, 0x5A,  5 }, /* Cranium */
	{ F_C,F_A, 0, 0x1C,  6 }, /* Crown & Anchor */
	{ F_D,F_R, 0, 0x60,  4 }, /* Dreidel */
	{ F_D,F_I, 0, 0x5F,  4 }, /* Dreidel - Israel */
	{ F_H,F_O, 0, 0x42,  6 }, /* Hotels */
	{ F_L,F_C, 0, 0x55,  6 }, /* LCR */
	{ F_M,F_W, 0, 0x10,  6 }, /* Mahjong Winds */
	{ F_M,F_S, 0, 0x0D,  3 }, /* Mahjong Suits */
	{ F_P,F_6, 0, 0x07,  6 }, /* Poker 6 */
	{ F_P,F_8, 0, 0x05,  8 }, /* Poker 8 */
	{ F_R,F_3, 0, 0x3C,  3 }, /* Rock Paper Scissors */
	{ F_R,F_5, 0, 0x3C,  5 }, /* Rock Paper Scissors Lizard Spock */
	{ F_S,F_G, 0, 0x64, 20 }, /* Scattergories */
	{ F_Z,F_O, 0, 0x22, 12 }, /* Zodiac */
	{ F_P,F_N, 0, 0x30, 12 }, /* Planets - Nodes */
	{ F_P,F_E, 0, 0x2E, 12 }, /* Planets - Earth & Comet */
	{ F_A,F_B, 0, 0x64, 26 }, /* Alphabet */
	{ F_W,F_D, 1, 0x7E,  7 }, /* Weekdays */
	{ F_M,F_O, 1, 0x8C, 12 }, /* Months */
	{ F_C,F_4, 1, 0xA4,  4 }, /* Compass Points 4 */
	{ F_C,F_8, 1, 0xA4,  8 }, /* Compass Points 8 */
	{ F_S,F_2, 0, 0xB4,  2 }, /* Spinner 2 */
	{ F_S,F_4, 0, 0xB4,  4 }, /* Spinner 4 */
	{ F_S,F_8, 0, 0xB4,  8 }, /* Spinner 8 */
};

static unsigned char special_dice_data[188] PROGMEM = {
	/* -- Card Ranks -- */
	/* 00 */ F_2,
	/* 01 */ F_3,
	/* 02 */ F_4,
	/* 03 */ F_5,
	/* 04 */ F_6,
	/* 05 */ F_7,
	/* 06 */ F_8,
	/* 07 */ F_9,
	/* 08 */ F_10,
	/* 09 */ F_J,
	/* 0A */ F_Q,
	/* 0B */ F_K,
	/* 0C */ F_A,
	/* -- Mahjong Suits -- */
	/* 0D */ F_DOT,
	/* 0E */ F_BAM,
	/* 0F */ F_CRAK,
	/* -- Mahjong Winds -- */
	/* 10 */ F_RED_DRAGON,
	/* 11 */ F_GREEN_DRAGON,
	/* 12 */ F_EAST,
	/* 13 */ F_SOUTH,
	/* 14 */ F_WEST,
	/* 15 */ F_NORTH,
	/* -- Chess -- */
	/* 16 */ F_W_PAWN,
	/* 17 */ F_W_KNIGHT,
	/* 18 */ F_W_BISHOP,
	/* 19 */ F_W_ROOK,
	/* 1A */ F_W_QUEEN,
	/* 1B */ F_W_KING,
	/* -- Card Suits / Crown & Anchor -- */
	/* 1C */ F_W_SPADE,
	/* 1D */ F_W_CLUB,
	/* 1E */ F_W_DIAMOND,
	/* 1F */ F_W_HEART,
	/* 20 */ F_W_KING,
	/* 21 */ F_ANCHOR,
	/* -- Zodiac -- */
	/* 22 */ F_ARIES,
	/* 23 */ F_TAURUS,
	/* 24 */ F_GEMINI,
	/* 25 */ F_CANCER,
	/* 26 */ F_LEO,
	/* 27 */ F_VIRGO,
	/* 28 */ F_LIBRA,
	/* 29 */ F_SCORPIO,
	/* 2A */ F_SAGITTARIUS,
	/* 2B */ F_CAPRICORN,
	/* 2C */ F_AQUARIUS,
	/* 2D */ F_PISCES,
	/* -- Planets -- */
	/* 2E */ F_COMET,
	/* 2F */ F_EARTH,
	/* 30 */ F_SUN,
	/* 31 */ F_MOON,
	/* 32 */ F_MERCURY,
	/* 33 */ F_VENUS,
	/* 34 */ F_MARS,
	/* 35 */ F_JUPITER,
	/* 36 */ F_SATURN,
	/* 37 */ F_URANUS,
	/* 38 */ F_NEPTUNE,
	/* 39 */ F_PLUTO,
	/* 3A */ F_ASCENDING_NODE,
	/* 3B */ F_DESCENDING_NODE,
	/* -- RPS -- */
	/* 3C */ F_ROCK,
	/* 3D */ F_PAPER,
	/* 3E */ F_SCISSORS,
	/* 3F */ F_LIZARD,
	/* 40 */ F_SPOCK,
	/* -- Coin Flip -- */
	/* 41 */ F_T,
	/* -- Coin Flip / Hotels -- */
	/* 42 */ F_H,
	/* -- Hotels -- */
	/* 43 */ F_2,
	/* 44 */ F_Y,
	/* 45 */ F_Y,
	/* -- Hotels / YesNo -- */
	/* 46 */ F_Y,
	/* 47 */ F_N,
	/* -- Backgammon -- */
	/* 48 */ F_1,
	/* 49 */ F_2,
	/* 4A */ F_4,
	/* 4B */ F_8,
	/* 4C */ F_16,
	/* 4D */ F_32,
	/* 4E */ F_64,
	/* 4F */ F_128,
	/* -- Bowling -- */
	/* 50 */ F_PIN,
	/* 51 */ F_PIN,
	/* 52 */ F_PIN,
	/* 53 */ F_PIN,
	/* 54 */ F_PIN,
	/* -- Bowling/LCR -- */
	/* 55 */ F_BLANK,
	/* -- LCR -- */
	/* 56 */ F_BLANK,
	/* 57 */ F_BLANK,
	/* 58 */ F_L,
	/* 59 */ F_C,
	/* -- LCR/Cranium -- */
	/* 5A */ F_R,
	/* -- Cranium -- */
	/* 5B */ F_Y,
	/* 5C */ F_B,
	/* 5D */ F_G,
	/* 5E */ F_V,
	/* -- Dreidel -- */
	/* 5F */ F_PEI,
	/* 60 */ F_NUN,
	/* 61 */ F_GIMEL,
	/* 62 */ F_HEI,
	/* 63 */ F_SHIN,
	/* -- Scattergories -- */
	/* 64 */ F_A,
	/* 65 */ F_B,
	/* 66 */ F_C,
	/* 67 */ F_D,
	/* 68 */ F_E,
	/* 69 */ F_F,
	/* 6A */ F_G,
	/* 6B */ F_H,
	/* 6C */ F_I,
	/* 6D */ F_J,
	/* 6E */ F_K,
	/* 6F */ F_L,
	/* 70 */ F_M,
	/* 71 */ F_N,
	/* 72 */ F_O,
	/* 73 */ F_P,
	/* 74 */ F_R,
	/* 75 */ F_S,
	/* 76 */ F_T,
	/* 77 */ F_W,
	/* 78 */ F_Q,
	/* 79 */ F_U,
	/* 7A */ F_V,
	/* 7B */ F_X,
	/* 7C */ F_Y,
	/* 7D */ F_Z,
	/* -- Weekdays -- */
	/* 7E */ F_S, F_u,
	/* 80 */ F_M, F_o,
	/* 82 */ F_T, F_u,
	/* 84 */ F_W, F_e,
	/* 86 */ F_T, F_h,
	/* 88 */ F_F, F_r,
	/* 8A */ F_S, F_a,
	/* -- Months -- */
	/* 8C */ F_J, F_n,
	/* 8E */ F_F, F_b,
	/* 90 */ F_M, F_r,
	/* 92 */ F_A, F_r,
	/* 94 */ F_M, F_y,
	/* 96 */ F_J, F_n,
	/* 98 */ F_J, F_l,
	/* 9A */ F_A, F_g,
	/* 9C */ F_S, F_p,
	/* 9E */ F_O, F_t,
	/* A0 */ F_N, F_v,
	/* A2 */ F_D, F_c,
	/* -- Compass Points -- */
	/* A4 */ F_N, 0,
	/* A6 */ F_E, 0,
	/* A8 */ F_S, 0,
	/* AA */ F_W, 0,
	/* AC */ F_N, F_W,
	/* AE */ F_N, F_E,
	/* B0 */ F_S, F_E,
	/* B2 */ F_S, F_W,
	/* -- Spinner -- */
	/* B4 */ F_UP,
	/* B5 */ F_DOWN,
	/* B6 */ F_LEFT,
	/* B7 */ F_RIGHT,
	/* B8 */ F_UP_LEFT,
	/* B9 */ F_UP_RIGHT,
	/* BA */ F_DOWN_RIGHT,
	/* BB */ F_DOWN_LEFT,
};

unsigned char get_special_dice_info(unsigned char i, unsigned char j) {
	return pgm_read_byte(&(special_dice_info[i][j]));
}

void display_special_dice(unsigned char i, unsigned char j) {
	unsigned char halfwd = pgm_read_byte(&(special_dice_info[i][2]));
	unsigned char offset = pgm_read_byte(&(special_dice_info[i][3])) + (j << halfwd);
	unsigned char a = pgm_read_byte(&(special_dice_data[offset]));
	if (halfwd) {
		unsigned char b = pgm_read_byte(&(special_dice_data[offset + 1]));
		display_chars(a, b);
	} else {
		display_char_8x8(a);
	}
}