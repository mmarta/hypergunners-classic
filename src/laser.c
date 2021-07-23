#include "laser.h"

void LaserFire(Laser *, u8, u8);

void LaserInit(Laser *laser) {
    laser->active = 0;
}

void LaserFire(Laser *laser, u8 x, u8 y) {
    laser->x = x;
    laser->y = y;
    laser->halfStep = 1; // For when we move to half-steps
    laser->active = 1;
    laser->skipFrame = 1;

    DrawMap(x, y, mapLaserPlayerFull);
}

void LaserFireNext(Laser lasers[], u8 len, u8 x, u8 y) {
    u8 i = 0;
    while(i < len) {
        if(!lasers[i].active) {
            LaserFire(&lasers[i], x, y);
            return;
        }
        i++;
    }
}

void LaserUpdate(Laser *laser) {
    if(!laser->active) {
        return;
    } else if(laser->skipFrame) {
        // So that we don't update the first frame we fired
        laser->skipFrame = 0;
        return;
    }

    if(laser->x <= END_POINT_X && !laser->halfStep) {
        LaserDeactivate(laser);
        return;
    } else if(laser->x < SPLIT_POINT_X) {
        if(laser->halfStep) {
            laser->halfStep = 0;
        } else {
            laser->x--;
            laser->halfStep = 1;
        }
    } else {
        laser->x--;
    }

    if(laser->x < SPLIT_POINT_X) {
        if(laser->halfStep) {
            Fill(laser->x + 1, laser->y, LASER_W, LASER_H, 0);
            DrawMap(laser->x, laser->y, mapLaserPlayerBottom);
        } else {
            DrawMap(laser->x, laser->y, mapLaserPlayerTop);
        }
    } else {
        Fill(laser->x + 1, laser->y, LASER_W, LASER_H, 0);
        DrawMap(laser->x, laser->y, mapLaserPlayerFull);
    }
}

void LaserDeactivate(Laser *laser) {
    laser->active = 0;
    Fill(laser->x, laser->y, LASER_W, LASER_H, 0);
}
