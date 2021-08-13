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

const char *mapWhipline[] = {
    mapWhipline0,
    mapWhipline1,
    mapWhipline2,
    mapWhipline3
};

const char *mapEnemy[] = {
    mapEnemy0,
    mapEnemy1,
    mapEnemy2,
    mapEnemy3,
    mapEnemy4,
    mapEnemy5
};

const char *mapEnemyPre[] = {
    mapEnemyPre0,
    mapEnemyPre1,
    mapEnemyPre2
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
