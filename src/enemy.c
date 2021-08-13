#include "enemy.h"

Enemy enemies[ENEMY_COUNT];

void EnemyInit(Enemy *);
void EnemyDraw(Enemy *);
void EnemyDeactivate(Enemy *);

void EnemyInitNext() {
    u8 i = ENEMY_COUNT;
    while(i--) {
        if(!enemies[i].active) {
            EnemyInit(&enemies[i]);
            return;
        }
    }
}

void EnemyInit(Enemy *enemy) {
    enemy->lane = rand() % 9; // Pick random lane.
    enemy->y = 1 + (enemy->lane * 3);
    enemy->x = END_POINT_X;
    enemy->active = 1;
    enemy->dieTime = 0;
    enemy->moveTime = 0;
    enemy->score = 1;
    enemy->preTime = 30;
    EnemyDraw(enemy);
}

u8 EnemyIsCollidable(Enemy *enemy) {
    return enemy->active && !enemy->dieTime && !enemy->preTime;
}

void EnemyKill(Enemy *enemy) {
    enemy->dieTime = 1;
}

void EnemyUpdate(Enemy *enemy) {
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
    if(enemy->animTime >= 12) {
        enemy->animTime = 0;
    }

    enemy->moveTime++;
    if(enemy->moveTime == 30) {
        if(enemy->x == LANE_BOTTOM_X - 1) {
            EnemyDeactivate(enemy);
        } else {
            Fill(enemy->x, enemy->y, 1, ENEMY_SIZE, 0);
            enemy->x++;
            EnemyDraw(enemy);
        }
        enemy->moveTime = 0;
    } else if(!(enemy->animTime % 2)) {
        EnemyDraw(enemy);
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
        if(bgTime < 8) {
            DrawMap(BACKGROUND_LINE_X - 1, enemy->y, mapEnemyPre[0]);
        } else if(bgTime < 16 || bgTime >= 24) {
            DrawMap(BACKGROUND_LINE_X - 1, enemy->y, mapEnemyPre[1]);
        } else {
            DrawMap(BACKGROUND_LINE_X - 1, enemy->y, mapEnemyPre[2]);
        }
        return;
    }

    DrawMap(enemy->x, enemy->y, mapEnemy[enemy->animTime >> 1]);
}

void EnemyDeactivate(Enemy *enemy) {
    enemy->active = 0;
    enemy->dieTime = 0;
    Fill(enemy->x, enemy->y, ENEMY_SIZE, ENEMY_SIZE, 0);
}
