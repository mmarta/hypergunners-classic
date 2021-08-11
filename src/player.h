#ifndef HGC_PLAYER_H
#define HGC_PLAYER_H

#include "defines.h"
#include "system.h"
#include "gfx.h"
#include "laser.h"
#include "whipline.h"

#define PLAYER_COUNT 2
#define PLAYER_X 28
#define PLAYER_SIZE 2

#define PLAYER_LASER_COUNT 2
#define PLAYER_EXTRA_LASER_COUNT 4

typedef struct {
    u8 lane, x, y, active, animTime, killTime, index, destY, clawTime, scoreDelta;
    u8 fireButton, whipButton, leftStick, rightStick;
    u16 score;
    Laser lasers[PLAYER_LASER_COUNT];
    Laser extraLasers[PLAYER_EXTRA_LASER_COUNT];
    Whipline whipline;
} Player;

extern Player players[];

void PlayerInit(Player *, u8);
u8 PlayerIsControllable(Player *);
void PlayerInput(Player *);
void PlayerUpdate(Player *);

#endif
