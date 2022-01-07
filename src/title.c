#include "title.h"

u16 titleTime;

void TitlePrintHighScores();

void StartTitle() {
    titleTime = 0;

    SetTileTable(gfxTitleTiles);
    ClearVram();

    PrintU8Vertical(30, 10, credits);
    PrintVerticalRAM(30, 17, "CREDIT");
}

void TitlePrintHighScores() {
    u8 x;
    Fill(0, 0, 30, 28, 0);

    PrintVerticalRAM(6, 19, "TODAY'S BEST");
    for(u8 i = 0; i < HIGH_SCORE_COUNT; i++) {
        x = 8 + (i << 1);
        PrintU16Vertical(x, 6, highScores[i], 50000, 1);
        PrintVerticalChar(x, 21, highScoreInitials[(i * 3)]);
        PrintVerticalChar(x, 20, highScoreInitials[(i * 3) + 1]);
        PrintVerticalChar(x, 19, highScoreInitials[(i * 3) + 2]);
    }
}

u8 UpdateTitle() {
    switch(titleTime) {
        case 0:
            ClearVram();
            PrintU8Vertical(30, 10, credits);
            PrintVerticalRAM(30, 17, "CREDIT");
            break;
        case 40:
            PrintVerticalRAM(6, 19, "RED  BALLTOP");
            break;
        case 80:
            PrintVerticalRAM(8, 17, "PRESENTS");
            break;
        case 120:
            DrawMap(10, 2, mapLogo);
            PrintVerticalRAM(13, 8, "CLASSIC");
            break;
        case 180:
            PrintVerticalRAM(15, 22, "@2022 RED BALLTOP");
            break;
        case 420:
            TitlePrintHighScores();
            break;
    }

    if(credits) {
        if(controls[0] & BTN_START) {
            credits--;
            return 1;
        } else if(controls[1] & BTN_START) {
            credits--;
            return 2;
        }
    }

    titleTime++;
    if(titleTime >= 600) {
        titleTime = 0;
    }

    return 0;
}
