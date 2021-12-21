#include "gfx.h"

#include "../data/gfx/gfx.inc"

const char *mapPlayer[] = {
    mapPlayer0,
    mapPlayer1,
    mapPlayer2,
    mapPlayer3,
    mapPlayer4,
    mapPlayer5,
    mapPlayer6,
    mapPlayer7
};

const char *mapPlayerExplode[] = {
    mapPlayerExplode0,
    mapPlayerExplode1,
    mapPlayerExplode2,
    mapPlayerExplode3
};

const char *mapPlayerMini[] = {
    mapPlayerMini0,
    mapPlayerMini1
};

const char *mapWhipline[] = {
    mapWhipline0,
    mapWhipline1,
    mapWhipline2,
    mapWhipline3
};

const char *mapEnemyStandard[] = {
    mapEnemyStandard0,
    mapEnemyStandard1,
    mapEnemyStandard2,
    mapEnemyStandard3,
    mapEnemyStandard4,
    mapEnemyStandard5
};

const char *mapEnemyStandardFar[] = {
    mapEnemyStandardFar0,
    mapEnemyStandardFar1,
    mapEnemyStandardFar2
};

const char *mapEnemyStandardPre[] = {
    mapEnemyStandardPre0,
    mapEnemyStandardPre1,
    mapEnemyStandardPre2
};

const char *mapEnemyThruster[] = {
    mapEnemyThruster0,
    mapEnemyThruster1,
    mapEnemyThruster2
};

const char *mapEnemyThrusterFar[] = {
    mapEnemyThrusterFar0,
    mapEnemyThrusterFar1
};

const char *mapEnemyThrusterPre[] = {
    mapEnemyThrusterPre0,
    mapEnemyThrusterPre1,
    mapEnemyThrusterPre2
};

const char *mapEnemyHawkeye[] = {
    mapEnemyHawkeye0,
    mapEnemyHawkeye1,
    mapEnemyHawkeye2
};

const char *mapEnemyBola[] = {
    mapEnemyBola0,
    mapEnemyBola1,
    mapEnemyBola2,
    mapEnemyBola3
};

const char *mapEnemyExplode[] = {
    mapEnemyExplode0,
    mapEnemyExplode1,
    mapEnemyExplode2,
    mapEnemyExplode3
};

const char mapLaserPlayerFull[] PROGMEM = {
    1,2,
    LASER_TILE_START + 1, LASER_TILE_START
};

const char mapLaserPlayerTop[] PROGMEM = {
    1,2,
    LASER_TILE_START + 3, LASER_TILE_START + 2
};

const char mapLaserPlayerBottom[] PROGMEM = {
    1,2,
    LASER_TILE_START + 5, LASER_TILE_START + 4
};


void PrintVerticalPROGMEM(u8 x, u8 y, const char *str) {
    u8 i = 0, c = pgm_read_byte(&(str[i]));
    while(c) {
        SetTile(x, y--, c - 32);
        c = pgm_read_byte(&(str[++i]));
    }
}

void PrintVerticalRAM(u8 x, u8 y, const char *str) {
    u8 i = 0;
    while(str[i]) {
        SetTile(x, y--, str[i] - 32);
        i++;
    }
}


void PrintVerticalChar(u8 x, u8 y, char ch) {
    SetTile(x, y, ch - 32);
}

void PrintU8Vertical(u8 x, u8 y, u8 val) {
    u8 max = 0xff, first = 1, modVal;

    do {
        modVal = val % 10;
        SetTile(x, y++, !first && modVal == 0 && val == 0 ? 0 : modVal + 16);
        val /= 10;
        max /= 10;
        first = 0;
    } while(max > 0);
}

void PrintU16Vertical(u8 x, u8 y, u16 val, u16 maxVal, u8 padHundredScore) {
    u8 first = 1, modVal;

    if(padHundredScore) {
        SetTile(x, y++, 16);
        SetTile(x, y++, 16);
    }

    do {
        modVal = val % 10;
        SetTile(x, y++, !first && modVal == 0 && val == 0 ? 0 : modVal + 16);
        val /= 10;
        maxVal /= 10;
        first = 0;
    } while(maxVal > 0);
}
