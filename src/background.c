#include "background.h"

u8 bgTime = 0;

void BackgroundStarsAnimate();

void BackgroundInit() {
    BackgroundStarsAnimate();
}

void BackgroundUpdate() {
    switch(bgTime) {
        case 0:
            Fill(BACKGROUND_LINE_X, 0, 1, 28, BACKGROUND_LINE_TILE_START);
            BackgroundStarsAnimate();
            break;
        case 8:
        case 24:
            Fill(BACKGROUND_LINE_X, 0, 1, 28, BACKGROUND_LINE_TILE_START + 1);
            BackgroundStarsAnimate();
            break;
        case 16:
            Fill(BACKGROUND_LINE_X, 0, 1, 28, 0);
            BackgroundStarsAnimate();
    }

    bgTime++;
    if(bgTime >= 32) {
        bgTime = 0;
    }
}

void BackgroundStarsAnimate() {
    u8 i, j, tile, updated = 0, jAdder;

    switch(bgTime) {
        case 0:
            tile = 0;
            break;
        case 8:
        case 24:
            tile = BACKGROUND_STAR_TILE_START + 2;
            break;
        case 16:
            tile = BACKGROUND_STAR_TILE_START;
    }

    i = 0;
    while(i < 28) {
        j = 17;
        jAdder = 1;
        while(j < 28) {
            SetTile(j, i, tile);
            j += jAdder;
            jAdder++;
        }

        i += 3;

        if(i >= 14 && !updated) {
            if(bgTime) {
                tile++;
            }
            updated = 1;
        }
    }
}
