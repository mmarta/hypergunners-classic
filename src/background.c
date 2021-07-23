#include "background.h"

u8 bgTime = 0;

void BackgroundInit() {
}

void BackgroundUpdate() {
    u8 i, j, tile, tileStart = BACKGROUND_STAR_TILE_START, modTime = bgTime % 8, doubleModTime = (bgTime << 1) % 8,
        quadModTime = (bgTime << 2) % 8, modLevel, modRange, updated = 0;

    switch(bgTime) {
        case 0:
            Fill(BACKGROUND_LINE_X, 0, 1, 28, BACKGROUND_LINE_TILE_START);
            break;
        case 8:
        case 24:
            Fill(BACKGROUND_LINE_X, 0, 1, 28, BACKGROUND_LINE_TILE_START + 1);
            break;
        case 16:
            Fill(BACKGROUND_LINE_X, 0, 1, 28, 0);
    }

    // Star updates
    i = 0;
    while(i < 28) {
        Fill(17, i, 1, 1, i >= 14 ? BACKGROUND_STAR_TILE_START + 8 + modTime : BACKGROUND_STAR_TILE_START + modTime);

        j = 18;
        while(j < 28) {
            if(j < SPLIT_POINT_X) {
                modLevel = 2;
                modRange = 4;
                tile = tileStart + doubleModTime;
            } else {
                modLevel = 4;
                modRange = 2;
                tile = tileStart + quadModTime;
            }

            if(modTime / modRange == j % modLevel) {
                SetTile(j, i, tile);
            } else {
                SetTile(j, i, 0);
            }
            j++;
        }

        i += 3;

        if(i >= 14 && !updated) {
            tileStart += 8;
            updated = 1;
        }
    }

    bgTime++;
    if(bgTime >= 32) {
        bgTime = 0;
    }
}
