#include "defines.h"
#include "system.h"
#include "gfx.h"
#include "background.h"
#include "player.h"
#include "enemy.h"

int main() {
    u8 i;
    srand(GetTrueRandomSeed());

    SetTileTable(gfxTiles);
    ClearVram();

    BackgroundInit();
    PlayerInit(&players[0], 0);

    while(1) {
        WaitVsync(1);

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
