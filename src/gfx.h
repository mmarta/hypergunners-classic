#ifndef HGC_GFX_H
#define HGC_GFX_H

#include "defines.h"

#define LASER_TILE_START 206

extern const char gfxTiles[];

extern const char *mapPlayer[];
extern const char *mapPlayerExplode[];
extern const char *mapWhipline[];
extern const char *mapEnemy[];
extern const char *mapEnemyPre[];
extern const char *mapEnemyExplode[];

extern const char mapPlayerHalfClawLeft[];
extern const char mapPlayerClawLeft[];
extern const char mapPlayerHalfClawRight[];
extern const char mapPlayerClawRight[];
extern const char mapPlayerClawWire[];

extern const char mapLaserPlayerFull[];
extern const char mapLaserPlayerTop[];
extern const char mapLaserPlayerBottom[];

extern const char mapEnemyLaser[];

void PrintVerticalPROGMEM(u8, u8, const char *);
void PrintVerticalRAM(u8, u8, const char *);
void PrintU8Vertical(u8, u8, u8);
void PrintU16Vertical(u8, u8, u16, u16, u8);

#endif
