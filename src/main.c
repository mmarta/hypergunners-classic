#include "defines.h"
#include "system.h"
#include "gfx.h"
#include "background.h"
#include "player.h"
#include "enemy.h"
#include "game.h"

int main() {
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
        ReadControls();

        if(gameMode == GAME) {
            UpdateGame();
        } else if(gameMode == SCORE_ENTRY) {
            UpdateScoreEntry();
        }
    }

    return 0;
}
