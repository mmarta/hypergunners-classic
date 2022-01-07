#include "system.h"

int controls[TOTAL_CONTROLS];
u8 coinSwitchDown = 0;
u8 credits = 0;

u16 highScores[] = {
    100,
    80,
    60,
    40,
    20
};

char highScoreInitials[] = {
    'R', 'B', 'T',
    'M', 'R', 'M',
    'S', 'L', 'M',
    'B', 'A', 'M',
    'D', 'M', 'M'
};

void ReadControls() {
    controls[0] = ReadJoypad(0);
    controls[1] = ReadJoypad(1);
}

u8 Coins() {
    // Coin/Service
    if(controls[0] & BTN_SL || controls[1] & BTN_SL || controls[1] & BTN_SR) {
        if(!coinSwitchDown) {
            if(credits < 9) {
                credits++;
            }
            //SFXPlay(PATCH_COIN_UP);
            coinSwitchDown = 1;
            return 1;
        }
    } else if(coinSwitchDown) {
        coinSwitchDown = 0;
    }

    return 0;
}
