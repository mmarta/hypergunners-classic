#include "defines.h"
#include "system.h"
#include "gfx.h"
#include "background.h"
#include "player.h"
#include "enemy.h"

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
                j++;
            }
        }

        ReadControls();
        PlayerInput(&players[0]);

        if(rand() % 200 == 0) {
            EnemyInitNext();
        }

        BackgroundUpdate();
        i = ENEMY_COUNT;
        while(i--) {
            EnemyUpdate(&enemies[i]);
        }
        PlayerUpdate(&players[0]);
    }

    return 0;
}
