#include "collision.h"

void CollisionLaserEnemy(Laser *laser, Enemy *enemy, Player *player) {
    if(!laser->active || !EnemyIsCollidable(enemy)) {
        return;
    }

    if(
        laser->x < ENEMY_SIZE + enemy->x && enemy->x < LASER_W + laser->x
        && laser->y < ENEMY_SIZE + enemy->y && enemy->y < LASER_H + laser->y
    ) {
        LaserDeactivate(laser);
        EnemyKill(enemy);
        player->scoreDelta += enemy->score;
    }
}

void CollisionWhiplineEnemy(Whipline *whipline, Enemy *enemy, Player *player) {
    if(!WhiplineIsCollidable(whipline) || !EnemyIsCollidable(enemy)) {
        return;
    }

    if(
        whipline->x < ENEMY_SIZE + enemy->x && enemy->x < WHIPLINE_W + whipline->x
        && whipline->y < ENEMY_SIZE + enemy->y && enemy->y < WHIPLINE_H + whipline->y
    ) {
        whipline->grabbedTime = 1;
        EnemyKill(enemy);
        player->scoreDelta += (enemy->score << 2);
    }
}
