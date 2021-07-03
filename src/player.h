#ifndef HYPERGUNNERS_CLASSIC_PLAYER_H
#define HYPERGUNNERS_CLASSIC_PLAYER_H

#include "defines.h"
#include "gfx.h"

#define PLAYER_COUNT 2
#define PLAYER_X 28

typedef struct {
    u8 lane, x, y, active, animTime, killTime, index;
    u16 score;
} Player;

extern Player players[];

void PlayerInit(Player *, u8);
void PlayerInput(Player *);
void PlayerUpdate(Player *);

#endif
