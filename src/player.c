#include "player.h"

Player players[PLAYER_COUNT];

void PlayerDraw(Player *);

void PlayerInit(Player *player, u8 index) {
    player->index = index;
    player->lane = 4;
    player->y = ((8 - player->lane) * 3) + 1;
    player->x = PLAYER_X;

    player->active = 1;
    player->animTime = 0;
    player->score = 0;

    if(index) {
        PrintVerticalRAM(0, 4, "2P");
        PrintU16Vertical(1, 0, player->score, 50000, 1);
    } else {
        PrintVerticalRAM(0, 24, "1P");
        PrintU16Vertical(1, 20, player->score, 50000, 1);
    }
}

void PlayerInput(Player *player) {

}

void PlayerUpdate(Player *player) {
    player->animTime++;
    if(player->animTime >= 12) {
        player->animTime = 0;
    }

    switch(player->animTime) {
        case 0:
        case 3:
        case 6:
        case 9:
            PlayerDraw(player);
    }
}

void PlayerDraw(Player *player) {
    u8 mapIndex = player->index ? 4 : 0;

    if(player->animTime < 3) {
        DrawMap(player->x, player->y, mapPlayer[mapIndex + 1]);
    } else if(player->animTime < 6 || player->animTime >= 9) {
        DrawMap(player->x, player->y, mapPlayer[mapIndex + 2]);
    } else {
        DrawMap(player->x, player->y, mapPlayer[mapIndex + 3]);
    }
}
