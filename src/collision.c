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

void CollisionLasers(Laser *laser, Laser *enemyLaser) {
    if(!laser->active || !enemyLaser->active) {
        return;
    }

    if(
        laser->x < enemyLaser->x + 2
        && laser->y < LASER_H + enemyLaser->y && enemyLaser->y < LASER_H + laser->y
    ) {
        LaserDeactivate(laser);
    }
}

void CollisionWhiplineLaser(Whipline *whipline, Laser *enemyLaser) {
    if(!WhiplineIsCollidable(whipline) || !enemyLaser->active) {
        return;
    }

    if(
        whipline->x < enemyLaser->x + 2
        && whipline->y < LASER_H + enemyLaser->y && enemyLaser->y < WHIPLINE_H + whipline->y
    ) {
        WhiplineDeactivate(whipline);
    }
}

void CollisionLaserPlayer(Laser *enemyLaser, Player *player) {
    if(!PlayerIsCollidable(player) || !enemyLaser->active) {
        return;
    }

    if(
        player->x < enemyLaser->x + 2
        && player->y < LASER_H + enemyLaser->y && enemyLaser->y < PLAYER_SIZE + player->y
    ) {
        PlayerKill(player);
    }
}

void CollisionPlayerEnemy(Player *player, Enemy *enemy) {
    if(!PlayerIsCollidable(player) || !EnemyIsCollidable(enemy)) {
        return;
    }

    if(
        player->x < ENEMY_SIZE + enemy->x && enemy->x < PLAYER_SIZE + player->x
        && player->y < ENEMY_SIZE + enemy->y && enemy->y < PLAYER_SIZE + player->y
    ) {
        PlayerKill(player);
        EnemyKill(enemy);
        player->scoreDelta += enemy->score;
    }
}
