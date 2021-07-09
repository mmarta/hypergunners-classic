#include "defines.h"
#include "gfx.h"
#include "background.h"
#include "player.h"

int main() {
    srand(GetTrueRandomSeed());

    SetTileTable(gfxTiles);
    ClearVram();

    BackgroundInit();
    PlayerInit(&players[0], 0);

    while(1) {
        WaitVsync(1);

        BackgroundUpdate();
        PlayerUpdate(&players[0]);
    }

    return 0;
}
