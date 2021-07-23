#include "player.h"

Player players[PLAYER_COUNT];

void PlayerLaunchClaw(Player *, u8);
void PlayerUpdateClaw(Player *);
void PlayerDraw(Player *);

void PlayerInit(Player *player, u8 index) {
    player->index = index;
    player->lane = 4;
    player->y = ((8 - player->lane) * 3) + 1;
    player->x = PLAYER_X;

    player->active = 1;
    player->animTime = 0;
    player->score = 0;

    player->clawTime = 0;
    player->fireButton = 0;
    player->leftStick = 0;
    player->rightStick = 0;

    if(index) {
        PrintVerticalRAM(0, 4, "2P");
        PrintU16Vertical(1, 0, player->score, 50000, 1);
    } else {
        PrintVerticalRAM(0, 24, "1P");
        PrintU16Vertical(1, 20, player->score, 50000, 1);
    }
}

u8 PlayerIsControllable(Player *player) {
    return player->active && !player->clawTime;
}

void PlayerInput(Player *player) {
    if(!PlayerIsControllable(player)) {
        return;
    }

    if(controls[player->index] & BTN_LEFT) {
        if(!player->leftStick) {
            if(player->y < 25) {
                PlayerLaunchClaw(player, player->y + 3);
            }
            player->leftStick = 1;
        }
    } else if(player->leftStick) {
        player->leftStick = 0;
    }

    if(controls[player->index] & BTN_RIGHT) {
        if(!player->rightStick) {
            if(player->y > 1) {
                PlayerLaunchClaw(player, player->y - 3);
            }
            player->rightStick = 1;
        }
    } else if(player->rightStick) {
        player->rightStick = 0;
    }

    if(controls[player->index] & BTN_A) {
        if(!player->fireButton) {
            LaserFireNext(player->lasers, PLAYER_LASER_COUNT, player->x - 1, player->y);
            player->fireButton = 1;
        }
    } else if(player->fireButton) {
        player->fireButton = 0;
    }
}

void PlayerLaunchClaw(Player *player, u8 destY) {
    if(player->clawTime > 0) {
        return;
    }

    player->clawTime = 1;
    player->destY = destY;
}

void PlayerUpdateClaw(Player *player) {
    if(player->clawTime >= 4) {
        if(player->destY < player->y) {
            Fill(player->x, player->y + 1, PLAYER_SIZE, 1, 0);
            player->y--;
        } else {
            Fill(player->x, player->y, PLAYER_SIZE, 1, 0);
            player->y++;
        }
        PlayerDraw(player);
    } else {
        if(player->destY < player->y) {
            switch(player->clawTime) {
                case 1:
                    DrawMap(player->x, player->y - 1, mapPlayerHalfClawRight);
                    break;
                case 2:
                    DrawMap(player->x, player->y - 2, mapPlayerClawRight);
                    break;
                default:
                    DrawMap(player->x, player->y - 3, mapPlayerClawRight);
                    DrawMap(player->x, player->y - 1, mapPlayerClawWire);
            }
        } else {
            switch(player->clawTime) {
                case 1:
                    DrawMap(player->x, player->y + 2, mapPlayerHalfClawLeft);
                    break;
                case 2:
                    DrawMap(player->x, player->y + 2, mapPlayerClawLeft);
                    break;
                default:
                    DrawMap(player->x, player->y + 3, mapPlayerClawLeft);
                    DrawMap(player->x, player->y + 2, mapPlayerClawWire);
            }
        }
    }

    player->clawTime++;
    if(player->clawTime >= 7) {
        player->clawTime = 0;
    }
}

void PlayerUpdate(Player *player) {
    if(!player->active) {
        return;
    }

    u8 i = 0;
    while(i < PLAYER_LASER_COUNT) {
        LaserUpdate(&player->lasers[i]);
        i++;
    }

    player->animTime++;
    if(player->animTime >= 12) {
        player->animTime = 0;
    }

    if(player->clawTime && !(player->animTime % 2)) {
        PlayerUpdateClaw(player);

        if(player->clawTime > 4) {
            return;
        }
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
