#ifndef SPECIAL_H
#define SPECIAL_H

#define SPECIAL_DICE_COUNT    32
#define SPECIAL_DICE_CHAR_0    0
#define SPECIAL_DICE_CHAR_1    1
#define SPECIAL_DICE_SIDES     4

unsigned char get_special_dice_info(unsigned char i, unsigned char j);
void display_special_dice(unsigned char i, unsigned char j);

#endif