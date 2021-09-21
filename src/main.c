#include "defines.h"
#include "system.h"
#include "gfx.h"
#include "background.h"
#include "player.h"
#include "enemy.h"
#include "collision.h"

int main() {
    u8 i, j, k;
    srand(GetTrueRandomSeed());

    SetTileTable(gfxTiles);
    ClearVram();

    BackgroundInit();
    PlayerInit(&players[0], 0);

    while(1) {
        WaitVsync(1);

        // Collision first
        i = ENEMY_COUNT;
        while(i--) {
            j = 0;
            while(j < PLAYER_COUNT) {
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
                j++;
            }
        }

        i = ENEMY_LASER_COUNT;
        while(i--) {
            j = 0;
            while(j < PLAYER_COUNT) {
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
                j++;
            }
        }

        ReadControls();
        PlayerInput(&players[0]);

        if(rand() % 50 == 0) {
            EnemyInitNext();
        }

        BackgroundUpdate();

        i = ENEMY_LASER_COUNT;
        while(i--) {
            EnemyLaserUpdate(&enemyLasers[i]);
        }

        i = ENEMY_COUNT;
        while(i--) {
            EnemyUpdate(&enemies[i]);
        }
        PlayerUpdate(&players[0]);
    }

    return 0;
}
