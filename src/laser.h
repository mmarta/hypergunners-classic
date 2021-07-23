#ifndef HYPERGUNNERS_CLASSIC_LASER_H
#define HYPERGUNNERS_CLASSIC_LASER_H

#include "defines.h"
#include "gfx.h"

#define LASER_W 1
#define LASER_H 2

typedef struct {
    u8 x, y, halfStep, active, skipFrame;
} Laser;

void LaserInit(Laser *);
void LaserFireNext(Laser[], u8, u8, u8);
void LaserUpdate(Laser *);
void LaserDeactivate(Laser *);

#endif
