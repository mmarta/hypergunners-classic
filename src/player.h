#ifndef HGC_PLAYER_H
#define HGC_PLAYER_H

#include "defines.h"
#include "system.h"
#include "gfx.h"
#include "laser.h"

#define PLAYER_COUNT 2
#define PLAYER_X 28
#define PLAYER_SIZE 2

#define PLAYER_LASER_COUNT 2

typedef struct {
    u8 lane, x, y, active, animTime, killTime, index, destY, clawTime;
    u8 fireButton, leftStick, rightStick;
    u16 score;
    Laser lasers[PLAYER_LASER_COUNT];
} Player;

extern Player players[];

void PlayerInit(Player *, u8);
u8 PlayerIsControllable(Player *);
void PlayerInput(Player *);
void PlayerUpdate(Player *);

#endif
