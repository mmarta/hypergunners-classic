#ifndef HYPERGUNNERS_CLASSIC_BACKGROUND_H
#define HYPERGUNNERS_CLASSIC_BACKGROUND_H

#include "defines.h"
#include "gfx.h"

#define BACKGROUND_STAR_TILE_START 176
#define BACKGROUND_LINE_TILE_START 192
#define BACKGROUND_STAR_POS_COUNT 6

extern u8 backgroundTime;

void BackgroundInit();
void BackgroundUpdate();

#endif
