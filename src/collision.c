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
};
