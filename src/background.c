#include "background.h"

const char mapBGWest0[] PROGMEM ={
8,1
,BACKGROUND_STAR_TILE_START,0,0,0,BACKGROUND_STAR_TILE_START + 8,0,0,0};

const char mapBGWest1[] PROGMEM ={
8,1
,BACKGROUND_STAR_TILE_START + 1,0,0,0,BACKGROUND_STAR_TILE_START + 9,0,0,0};

const char mapBGWest2[] PROGMEM ={
8,1
,0,BACKGROUND_STAR_TILE_START + 2,0,0,0,BACKGROUND_STAR_TILE_START + 10,0,0};

const char mapBGWest3[] PROGMEM ={
8,1
,0,BACKGROUND_STAR_TILE_START + 3,0,0,0,BACKGROUND_STAR_TILE_START + 11,0,0};

const char mapBGWest4[] PROGMEM ={
8,1
,0,0,BACKGROUND_STAR_TILE_START + 4,0,0,0,BACKGROUND_STAR_TILE_START + 12,0};

const char mapBGWest5[] PROGMEM ={
8,1
,0,0,BACKGROUND_STAR_TILE_START + 5,0,0,0,BACKGROUND_STAR_TILE_START + 13,0};

const char mapBGWest6[] PROGMEM ={
8,1
,0,0,0,BACKGROUND_STAR_TILE_START + 6,0,0,0,BACKGROUND_STAR_TILE_START + 14};

const char mapBGWest7[] PROGMEM ={
8,1
,0,0,0,BACKGROUND_STAR_TILE_START + 7,0,0,0,BACKGROUND_STAR_TILE_START + 15};

const char mapBGEast0[] PROGMEM ={
8,1
,BACKGROUND_STAR_TILE_START + 14,0,0,0,BACKGROUND_STAR_TILE_START + 6,0,0,0};

const char mapBGEast1[] PROGMEM ={
8,1
,BACKGROUND_STAR_TILE_START + 15,0,0,0,BACKGROUND_STAR_TILE_START + 7,0,0,0};

const char mapBGEast2[] PROGMEM ={
8,1
,0,BACKGROUND_STAR_TILE_START + 12,0,0,0,BACKGROUND_STAR_TILE_START + 4,0,0};

const char mapBGEast3[] PROGMEM ={
8,1
,0,BACKGROUND_STAR_TILE_START + 13,0,0,0,BACKGROUND_STAR_TILE_START + 5,0,0};

const char mapBGEast4[] PROGMEM ={
8,1
,0,0,BACKGROUND_STAR_TILE_START + 10,0,0,0,BACKGROUND_STAR_TILE_START + 2,0};

const char mapBGEast5[] PROGMEM ={
8,1
,0,0,BACKGROUND_STAR_TILE_START + 11,0,0,0,BACKGROUND_STAR_TILE_START + 3,0};

const char mapBGEast6[] PROGMEM ={
8,1
,0,0,0,BACKGROUND_STAR_TILE_START + 8,0,0,0,BACKGROUND_STAR_TILE_START};

const char mapBGEast7[] PROGMEM ={
8,1
,0,0,0,BACKGROUND_STAR_TILE_START + 9,0,0,0,BACKGROUND_STAR_TILE_START + 1};

const char *mapBGWest[] = {
    mapBGWest0, mapBGWest1,
    mapBGWest2, mapBGWest3,
    mapBGWest4, mapBGWest5,
    mapBGWest6, mapBGWest7
};

const char *mapBGEast[] = {
    mapBGEast0, mapBGEast1,
    mapBGEast2, mapBGEast3,
    mapBGEast4, mapBGEast5,
    mapBGEast6, mapBGEast7
};

u8 bgTime = 0;
u8 bgStarPos[BACKGROUND_STAR_POS_COUNT];

void BackgroundInit() {
    u8 i = BACKGROUND_STAR_POS_COUNT;
    while(i--) {
        bgStarPos[i] = rand() % 8;
    }
}

void BackgroundUpdate() {
    u8 tileY, tileX, i, j;

    switch(bgTime) {
        case 0:
            Fill(11, 0, 1, 28, BACKGROUND_LINE_TILE_START);
            break;
        case 8:
        case 24:
            Fill(11, 0, 1, 28, BACKGROUND_LINE_TILE_START + 1);
            break;
        case 16:
            Fill(11, 0, 1, 28, 0);
    }

    // Star updates
    if(1) {
        i = BACKGROUND_STAR_POS_COUNT;
        while(i--) {
            bgStarPos[i]++;
            if(bgStarPos[i] >= 8) {
                bgStarPos[i] = 0;
            }
        }

        i = 0;
        tileY = 4;
        tileX = 12;
        while(i < 2) {
            j = 0;
            while(j < 2) {
                DrawMap(tileX + (j << 3), (tileY - j), mapBGEast[bgStarPos[i]]);
                j++;
            }
            tileY += 7;
            i++;
        }

        i = 0;
        tileY = 16;
        tileX = 12;
        while(i < 2) {
            j = 0;
            while(j < 2) {
                DrawMap(tileX + (j << 3), (tileY + j), mapBGWest[bgStarPos[i]]);
                j++;
            }
            tileY += 7;
            i++;
        }
    }

    bgTime++;
    if(bgTime >= 32) {
        bgTime = 0;
    }
}
