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
    if(laser->active) {
        laser->active = 0;
        Fill(laser->x, laser->y, LASER_W, LASER_H, 0);
    }
}

// ENEMY lasers

Laser enemyLasers[ENEMY_LASER_COUNT];

Laser * EnemyLaserFireNext(u8 x, u8 lane, LaserStyle laserStyle) {
    u8 i = 0;
    while(i < ENEMY_LASER_COUNT) {
        if(!enemyLasers[i].active) {
            EnemyLaserInit(&enemyLasers[i], x, lane, laserStyle);
            return &enemyLasers[i];
        }
        i++;
    }

    return NULL;
}

void EnemyLaserInit(Laser *laser, u8 x, u8 lane, LaserStyle laserStyle) {
    if(laserStyle == LASER_STYLE_ENEMY_STRAIGHT) {
        laser->x = x;
        laser->startX = x;
        laser->lane = lane;
        laser->y = CALC_Y_FROM_LANE(lane);
        laser->time = 0;
        DrawMap(laser->x, laser->y, mapEnemyLaser);
    }
    laser->laserStyle = laserStyle;
    laser->active = 1;
}

void EnemyLaserUpdate(Laser *laser) {
    if(!laser->active) {
        return;
    }

    u8 drawIndex;

    if(laser->x == LANE_BOTTOM_X) {
        laser->time++;

        if(laser->time >= ENEMY_LASER_STOP_TIME) {
            EnemyLaserDeactivate(laser);
            return;
        } else if(laser->time + (laser->x - laser->startX + 1) >= ENEMY_LASER_STOP_TIME) {
            Fill(laser->x - (ENEMY_LASER_STOP_TIME - laser->time), laser->y, LASER_W, LASER_H, 0);
        } else {
            drawIndex = laser->startX;
            while(drawIndex <= laser->x){
                DrawMap(drawIndex, laser->y, mapEnemyLaser);
                drawIndex++;
            }
        }
    } else {
        if(!laser->skipFrame) {
            laser->x++;
        }

        drawIndex = laser->startX;
        while(drawIndex <= laser->x){
            DrawMap(drawIndex, laser->y, mapEnemyLaser);
            drawIndex++;
        }

        laser->skipFrame++;
        if(laser->skipFrame >= 4) {
            laser->skipFrame = 0;
        }
    }

}

void EnemyLaserDeactivate(Laser *laser) {
    Fill(laser->x, laser->y, LASER_W, LASER_H, 0);
    laser->active = 0;
}
