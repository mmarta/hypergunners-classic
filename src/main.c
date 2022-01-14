#include "defines.h"
#include "system.h"
#include "gfx.h"
#include "background.h"
#include "player.h"
#include "game.h"
#include "title.h"

int main() {
    u8 returnVal;
    srand(GetTrueRandomSeed());

    gameMode = TITLE;
    StartTitle();

    BackgroundInit();
    PlayersInitMemory();

    // DEBUG CODE FOR REORDINGS
    do {
        ReadControls();
    } while(!(controls[0] & BTN_DOWN));

    while(1) {
        WaitVsync(1);
        ReadControls();

        if(Coins()) {
            if(gameMode == TITLE) {
                PrintU8Vertical(30, 10, credits);
                PrintVerticalRAM(30, 17, "CREDIT");
                CoinedTitle();
            }
        }

        if(gameMode == GAME) {
            UpdateGame();
            if(gameMode == TITLE) {
                StartTitle();
            }
        } else if(gameMode == SCORE_ENTRY) {
            UpdateScoreEntry();
            if(gameMode == TITLE) {
                StartTitle();
            }
        } else if(gameMode == TITLE) {
            returnVal = UpdateTitle();
            if(returnVal) {
                returnVal--;
                GameReset();
                PlayerInit(&players[returnVal], returnVal);
            }
        }

        repeatTicks++;
        if(repeatTicks >= 120) {
            repeatTicks = 0;
        }
    }

    return 0;
}
