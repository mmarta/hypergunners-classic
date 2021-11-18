#include "defines.h"
#include "system.h"
#include "gfx.h"
#include "background.h"
#include "player.h"
#include "enemy.h"
#include "collision.h"
#include "game.h"

int main() {
    u8 i, j, k, t = 0, playerCollisionCondition;
    srand(GetTrueRandomSeed());

    SetTileTable(gfxTiles);
    ClearVram();

    BackgroundInit();
    PlayerInit(&players[0], 0);
    //PlayerInit(&players[1], 1);

    GameReset();

    // DEBUG CODE FOR REORDINGS
    do {
        ReadControls();
    } while(!(controls[0] & BTN_DOWN));

    while(1) {
        WaitVsync(1);

        // Collision first
        i = ENEMY_COUNT;
        while(i--) {
            j = 0;
            playerCollisionCondition = t ? j < PLAYER_COUNT : j != 0xff;

            while(playerCollisionCondition) {
                k = 0;
                while(k < PLAYER_LASER_COUNT) {
                    CollisionLaserEnemy(&players[j].lasers[k], &enemies[i], &players[j]);
                    k++;
                }

                k = 0;
                while(k < PLAYER_EXTRA_LASER_COUNT) {
                    CollisionLaserEnemy(&players[j].extraLasers[k], &enemies[i], &players[j]);
                    k++;
                }

                CollisionWhiplineEnemy(&players[j].whipline, &enemies[i], &players[j]);

                CollisionPlayerEnemy(&players[j], &enemies[i]);

                if(t) {
                    j++;
                    playerCollisionCondition = j < PLAYER_COUNT;
                } else {
                    j--;
                    playerCollisionCondition = j != 0xff;
                }
            }
        }

        i = ENEMY_LASER_COUNT;
        while(i--) {
            j = 0;
            playerCollisionCondition = t ? j < PLAYER_COUNT : j != 0xff;

            while(playerCollisionCondition) {
                k = 0;
                while(k < PLAYER_LASER_COUNT) {
                    CollisionLasers(&players[j].lasers[k], &enemyLasers[i]);
                    k++;
                }

                k = 0;
                while(k < PLAYER_EXTRA_LASER_COUNT) {
                    CollisionLasers(&players[j].extraLasers[k], &enemyLasers[i]);
                    k++;
                }

                CollisionWhiplineLaser(&players[j].whipline, &enemyLasers[i]);

                CollisionLaserPlayer(&enemyLasers[i], &players[j]);
                if(t) {
                    j++;
                    playerCollisionCondition = j < PLAYER_COUNT;
                } else {
                    j--;
                    playerCollisionCondition = j != 0xff;
                }
            }
        }

        ReadControls();
        PlayerInput(&players[0]);
        PlayerInput(&players[1]);

        // Update spawn time and see if we generate a new enemy
        GameSpawnUpdate();

        BackgroundUpdate();
        GameUpdateRank();

        i = ENEMY_LASER_COUNT;
        while(i--) {
            EnemyLaserUpdate(&enemyLasers[i]);
        }

        i = ENEMY_COUNT;
        while(i--) {
            EnemyUpdate(&enemies[i]);
        }

        if(t) {
            PlayerUpdate(&players[1]);
            PlayerUpdate(&players[0]);
        } else {
            PlayerUpdate(&players[0]);
            PlayerUpdate(&players[1]);
        }

        t++;
        t = t % 2;
    }

    return 0;
}
