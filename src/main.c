#include "defines.h"
#include "gfx.h"
#include "player.h"

int main() {
    SetTileTable(gfxTiles);
    ClearVram();

    PlayerInit(&players[0], 0);

    while(1) {
        WaitVsync(1);

        PlayerUpdate(&players[0]);
    }

    return 0;
}
