#ifndef HYPERGUNNERS_CLASSIC_GFX_H
#define HYPERGUNNERS_CLASSIC_GFX_H

#include "defines.h"

#define LASER_TILE_START 194

extern const char gfxTiles[];

extern const char *mapPlayer[];

extern const char mapPlayerHalfClawLeft[];
extern const char mapPlayerClawLeft[];
extern const char mapPlayerHalfClawRight[];
extern const char mapPlayerClawRight[];
extern const char mapPlayerClawWire[];

extern const char mapLaserPlayerFull[];
extern const char mapLaserPlayerTop[];
extern const char mapLaserPlayerBottom[];

void PrintVerticalPROGMEM(u8, u8, const char *);
void PrintVerticalRAM(u8, u8, const char *);
void PrintU8Vertical(u8, u8, u8);
void PrintU16Vertical(u8, u8, u16, u16, u8);

#endif
