#ifndef HGC_SYSTEM_H
#define HGC_SYSTEM_H

#include "defines.h"

#define TOTAL_CONTROLS 2

#define HIGH_SCORE_COUNT 5

extern int controls[];
extern u8 credits;
extern u8 repeatTicks;

extern u16 highScores[];
extern char highScoreInitials[];

void ReadControls();
u8 Coins();

#endif
