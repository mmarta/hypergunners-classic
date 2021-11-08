#ifndef HGC_BACKGROUND_H
#define HGC_BACKGROUND_H

#include "defines.h"
#include "gfx.h"

#define BACKGROUND_STAR_TILE_START 64
#define BACKGROUND_LINE_TILE_START 68
#define BACKGROUND_STAR_POS_COUNT 6

#define BACKGROUND_LINE_X 16

extern u8 bgTime;

void BackgroundInit();
void BackgroundUpdate();

#endif
