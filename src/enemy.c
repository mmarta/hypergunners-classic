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
    EnemyDraw(enemy);
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
        }
        enemy->dieTime++;
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
        } else if(enemy->dieTime <= 4) {
            DrawMap(enemy->x, enemy->y, mapEnemyExplode[1]);
        } else if(enemy->dieTime <= 4) {
            DrawMap(enemy->x, enemy->y, mapEnemyExplode[2]);
        } else {
            DrawMap(enemy->x, enemy->y, mapEnemyExplode[3]);
        }
        return;
    }

    DrawMap(enemy->x, enemy->y, mapEnemy[enemy->animTime >> 1]);
}

void EnemyDeactivate(Enemy *enemy) {
    enemy->active = 0;
    Fill(enemy->x, enemy->y, ENEMY_SIZE, ENEMY_SIZE, 0);
}
