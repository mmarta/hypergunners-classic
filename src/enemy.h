#ifndef HGC_ENEMY_H
#define HGC_ENEMY_H

#include "defines.h"
#include "gfx.h"
#include "background.h"
#include "laser.h"

#define ENEMY_SIZE 2

#define ENEMY_COUNT 10

typedef enum {
    STANDARD,
    THRUSTER,
    HAWKEYE
} EnemyType;

typedef struct {
    u8 x, y, active, animTime, moveTime, dieTime, score, lane, preTime, alreadyFired;
    EnemyType type;
    Laser *currentLaser;
} Enemy;

extern Enemy enemies[];

void EnemyInitNext();
u8 EnemyIsCollidable(Enemy *);
void EnemyKill(Enemy *);
void EnemyUpdate(Enemy *);

#endif
