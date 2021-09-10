#ifndef HGC_LASER_H
#define HGC_LASER_H

#include "defines.h"
#include "gfx.h"

#define LASER_W 1
#define LASER_H 2

#define ENEMY_LASER_COUNT 8
#define ENEMY_LASER_STOP_TIME 40

typedef enum {
    LASER_STYLE_PLAYER,
    LASER_STYLE_ENEMY_STRAIGHT
} LaserStyle;

typedef struct {
    u8 lane, x, y, halfStep, active, skipFrame, time, startX;
    LaserStyle laserStyle;
} Laser;

extern Laser enemyLasers[];

void LaserInit(Laser *);
void LaserFireNext(Laser [], u8, u8, u8);
void LaserUpdate(Laser *);
void LaserDeactivate(Laser *);

Laser * EnemyLaserFireNext(u8, u8, LaserStyle);
void EnemyLaserInit(Laser *, u8, u8, LaserStyle);
void EnemyLaserUpdate(Laser *);
void EnemyLaserDeactivate(Laser *);

#endif
