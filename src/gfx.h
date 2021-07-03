#ifndef HYPERGUNNERS_CLASSIC_GFX_H
#define HYPERGUNNERS_CLASSIC_GFX_H

#include "defines.h"

extern const char gfxTiles[];

extern const char *mapPlayer[];

void PrintVerticalPROGMEM(u8, u8, const char *);
void PrintVerticalRAM(u8, u8, const char *);
void PrintU8Vertical(u8, u8, u8);
void PrintU16Vertical(u8, u8, u16, u16, u8);

#endif
