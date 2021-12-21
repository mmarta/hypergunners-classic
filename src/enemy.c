#include "enemy.h"

Enemy enemies[ENEMY_COUNT];

void EnemyInit(Enemy *, EnemyType, u8);
void EnemyFire(Enemy *);
void EnemyDraw(Enemy *);
void EnemyUpdateHawkeye(Enemy *);
void EnemyUpdateBola(Enemy *);

void EnemyInitNext(u8 weight) {
    u8 i = ENEMY_COUNT, fireFactor;

    while(i--) {
        if(!enemies[i].active) {
            // Use weight to figure out type
            if(weight > 10) {
                weight = 10 + rand() % 2;
                fireFactor = 55;
            } else if(weight >= 4) {
                weight += rand() % 2;
                fireFactor = 255 - (20 * weight);
            } else {
                fireFactor = 255;
            }
            EnemyType weightedType = (weight + rand() % 10) / 6;

            EnemyInit(&enemies[i], weightedType, fireFactor);
            return;
        }
    }
}

void EnemyInit(Enemy *enemy, EnemyType t, u8 fireFactor) {
    u8 i = 0;
    enemy->type = t;

    if(enemy->type == HAWKEYE) {
        enemy->lane = (rand() % 7) + 1;
        while(i < ENEMY_COUNT) {
            if(&enemies[i] != enemy && enemies[i].active && (enemies[i].type == HAWKEYE || enemies[i].lane == enemy->lane)) {
                return;
            }
            i++;
        }
    } else {
        enemy->lane = rand() % 9;
        while(i < ENEMY_COUNT) {
            if(&enemies[i] != enemy && enemies[i].active && enemies[i].type == HAWKEYE && enemies[i].lane == enemy->lane) {
                return;
            }
            i++;
        }
    }


    enemy->y = CALC_Y_FROM_LANE(enemy->lane);
    enemy->x = END_POINT_X;
    enemy->active = 1;
    enemy->animTime = 0;
    enemy->dieTime = 0;
    enemy->moveTime = 0;
    enemy->preTime = 30;
    switch(enemy->type) {
        case HAWKEYE:
            enemy->score = 0;
            enemy->x -= 6;
            enemy->preTime = 0;
            break;
        case BOLA:
            enemy->score= 4;
            enemy->preTime = 0;
            break;
        case THRUSTER:
            enemy->score = 2;
            break;
        default:
            enemy->score = 1;
    }

    enemy->fireFactor = fireFactor;
    enemy->alreadyFired = 0;
    enemy->currentLaser = NULL;
    EnemyDraw(enemy);
}

u8 EnemyIsCollidable(Enemy *enemy) {
    return enemy->active && !enemy->dieTime && !enemy->preTime;
}

void EnemyFire(Enemy *enemy) {
    u8 i = 0;

    if(enemy->currentLaser || enemy->alreadyFired || enemy->x > 20) {
        return;
    }

    while(i < ENEMY_COUNT) {
        if(&enemies[i] != enemy && enemies[i].active) {
            if(enemies[i].lane == enemy->lane) {
                return;
            }
        }

        i++;
    }

    enemy->currentLaser = EnemyLaserFireNext(enemy->x + 2, enemy->lane, LASER_STYLE_ENEMY_STRAIGHT);
    enemy->alreadyFired = 1;
}

void EnemyKill(Enemy *enemy) {
    enemy->dieTime = 1;
}

void EnemyUpdateHawkeye(Enemy *enemy) {
    u8 modTime = enemy->moveTime % 4;

    if(enemy->moveTime < 30) {
        if(!modTime) {
            EnemyDraw(enemy);
        } else if(modTime == 2) {
            Fill(enemy->x, enemy->y, ENEMY_SIZE, ENEMY_SIZE, 0);
        }
    } else if(enemy->moveTime == 90) {
        EnemyFire(enemy);
    } else if(enemy->moveTime >= 200) {
        EnemyDeactivate(enemy);
    } else if(enemy->animTime % 2 == 0) {
        EnemyDraw(enemy);
    }
}

void EnemyUpdateBola(Enemy *enemy) {
    u8 modTime;

    enemy->moveTime++;
    modTime = enemy->animTime % 4;

    if(enemy->x == LANE_BOTTOM_X - 1) {
        EnemyDeactivate(enemy);
        return;
    } else if(enemy->x == END_POINT_X) {
        if(enemy->moveTime < enemy->fireFactor >> 1) {
            if(!modTime) {
                EnemyDraw(enemy);
            }
        } else {
            Fill(enemy->x, enemy->y, ENEMY_SIZE, ENEMY_SIZE, 0);
            enemy->x++;
            EnemyDraw(enemy);
        }
    } else if(modTime == 0 || modTime == 2) {
        Fill(enemy->x, enemy->y, ENEMY_SIZE, ENEMY_SIZE, 0);
        enemy->x++;
        EnemyDraw(enemy);
    }
}

void EnemyUpdate(Enemy *enemy) {
    u8 moveTime = 30, animTime = 12;
    if(enemy->type == THRUSTER) {
        moveTime = 12;
    } else if(enemy->type == HAWKEYE || enemy->type == BOLA) {
        moveTime = 0;
    }

    if(enemy->type == BOLA) {
        animTime = 16;
    }

    if(!enemy->active) {
        return;
    }

    if(enemy->dieTime) {
        switch(enemy->dieTime) {
            case 1:
            case 5:
            case 9:
            case 13:
                EnemyDraw(enemy);
                break;
            case 17:
                EnemyDeactivate(enemy);
                return;
        }
        enemy->dieTime++;
        return;
    } else if(enemy->preTime) {
        enemy->preTime--;
        if(!enemy->preTime) {
            if(bgTime < 8) {
                Fill(BACKGROUND_LINE_X, enemy->y, 1, ENEMY_SIZE, BACKGROUND_LINE_TILE_START);
            } else if(bgTime < 16 || bgTime >= 24) {
                Fill(BACKGROUND_LINE_X, enemy->y, 1, ENEMY_SIZE, BACKGROUND_LINE_TILE_START + 1);
            } else {
                Fill(BACKGROUND_LINE_X, enemy->y, 1, ENEMY_SIZE, 0);
            }
            EnemyDraw(enemy);
        } else if(bgTime % 8 == 1) {
            EnemyDraw(enemy);
        }

        return;
    }

    enemy->animTime++;
    if(enemy->animTime >= animTime) {
        enemy->animTime = 0;
    }

    enemy->moveTime++;
    if(enemy->type == HAWKEYE) {
        EnemyUpdateHawkeye(enemy);
    } else if(enemy->type == BOLA) {
        EnemyUpdateBola(enemy);
    } else {
        if(enemy->currentLaser && !enemy->currentLaser->active) {
            enemy->currentLaser = NULL;
        } else if(rand() % enemy->fireFactor == 1) {
            EnemyFire(enemy);
        }

        if(enemy->moveTime == moveTime) {
            if(enemy->x == LANE_BOTTOM_X - 1) {
                EnemyDeactivate(enemy);
            } else {
                Fill(enemy->x, enemy->y, 1, ENEMY_SIZE, 0);
                if(!enemy->currentLaser) {
                    enemy->x++;
                }
                EnemyDraw(enemy);
            }
            enemy->moveTime = 0;
        } else if(!(enemy->animTime % 2)) {
            EnemyDraw(enemy);
        }
    }

}

void EnemyDraw(Enemy *enemy) {
    if(enemy->dieTime) {
        if(enemy->dieTime <= 4) {
            DrawMap(enemy->x, enemy->y, mapEnemyExplode[0]);
        } else if(enemy->dieTime <= 8) {
            DrawMap(enemy->x, enemy->y, mapEnemyExplode[1]);
        } else if(enemy->dieTime <= 12) {
            DrawMap(enemy->x, enemy->y, mapEnemyExplode[2]);
        } else {
            DrawMap(enemy->x, enemy->y, mapEnemyExplode[3]);
        }
        return;
    } else if(enemy->preTime) {
        if(enemy->type == THRUSTER) {
            if(bgTime < 8) {
                DrawMap(BACKGROUND_LINE_X - 1, enemy->y, mapEnemyThrusterPre[0]);
            } else if(bgTime < 16 || bgTime >= 24) {
                DrawMap(BACKGROUND_LINE_X - 1, enemy->y, mapEnemyThrusterPre[1]);
            } else {
                DrawMap(BACKGROUND_LINE_X - 1, enemy->y, mapEnemyThrusterPre[2]);
            }
        } else {
            if(bgTime < 8) {
                DrawMap(BACKGROUND_LINE_X - 1, enemy->y, mapEnemyStandardPre[0]);
            } else if(bgTime < 16 || bgTime >= 24) {
                DrawMap(BACKGROUND_LINE_X - 1, enemy->y, mapEnemyStandardPre[1]);
            } else {
                DrawMap(BACKGROUND_LINE_X - 1, enemy->y, mapEnemyStandardPre[2]);
            }
        }

        return;
    }

    if(enemy->type == HAWKEYE) {
        DrawMap(enemy->x, enemy->y, mapEnemyHawkeye[enemy->animTime >> 2]);
    } else if(enemy->type == THRUSTER) {
        DrawMap(enemy->x, enemy->y, enemy->x < SPLIT_POINT_X - 1 ? mapEnemyThrusterFar[enemy->animTime / 6] : mapEnemyThruster[enemy->animTime >> 2]);
    } else if(enemy->type == BOLA) {
        DrawMap(enemy->x, enemy->y, mapEnemyBola[enemy->animTime >> 2]);
    } else {
        DrawMap(enemy->x, enemy->y, enemy->x < SPLIT_POINT_X - 1 ? mapEnemyStandardFar[enemy->animTime >> 2] : mapEnemyStandard[enemy->animTime >> 1]);
    }

}

void EnemyDeactivate(Enemy *enemy) {
    enemy->active = 0;
    enemy->dieTime = 0;
    Fill(enemy->x, enemy->y, ENEMY_SIZE, ENEMY_SIZE, 0);
}
