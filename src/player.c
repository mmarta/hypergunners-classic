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
    player->superWeaponSeconds = 0;
    player->score = 0;
    player->scoreDelta = 0;
    player->superWeaponFireTimer = 0;

    player->clawTime = 0;
    player->fireButton = 0;
    player->whipButton = 0;
    player->leftStick = 0;
    player->rightStick = 0;

    player->whipline.usable = 1;

    if(index) {
        PrintVerticalRAM(0, 4, "2P");
        PrintU16Vertical(1, 0, player->score, 50000, 1);
    } else {
        PrintVerticalRAM(0, 24, "1P");
        PrintU16Vertical(1, 20, player->score, 50000, 1);
    }
}

u8 PlayerIsControllable(Player *player) {
    return player->active && !player->clawTime && !player->whipline.active;
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
            // Super Weapon Available? Fire that some frames later
            if(player->superWeaponSeconds && !player->superWeaponFireTimer) {
                player->superWeaponFireTimer = 6;
                player->superWeaponY = player->y;
            }

            player->fireButton = 1;
        }
    } else if(player->fireButton) {
        player->fireButton = 0;
    }

    if(controls[player->index] & BTN_B) {
        if(!player->whipButton) {
            WhiplineInit(&player->whipline, player->lane);
            player->whipButton = 1;
        }
    } else if(player->whipButton) {
        player->whipButton = 0;
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
    u8 laneUp = 1;

    if(player->clawTime >= 4) {
        if(player->destY < player->y) {
            Fill(player->x, player->y + 1, PLAYER_SIZE, 1, 0);
            player->y--;
            laneUp = 0;
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
        player->lane = player->lane + (laneUp ? 1 : -1);
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

    i = 0;
    while(i < PLAYER_EXTRA_LASER_COUNT) {
        LaserUpdate(&player->extraLasers[i]);
        i++;
    }

    if(WhiplineUpdate(&player->whipline)) {
        player->superWeaponSeconds = PLAYER_SUPER_WEAPON_MAX_SECONDS;
        player->timeOut = 60;
        PrintVerticalRAM(30, 16, "MULTI GUN TIME");
        PrintU8Vertical(30, 0, player->superWeaponSeconds);
    }

    if(player->superWeaponFireTimer == 1 && !player->extraLasers[0].active && !player->extraLasers[1].active) {
        if(player->y > 1) {
            LaserFireNext(player->extraLasers, PLAYER_EXTRA_LASER_COUNT, player->x - 1, player->superWeaponY - 3);
        }

        if(player->y < 25) {
            LaserFireNext(player->extraLasers, PLAYER_EXTRA_LASER_COUNT, player->x - 1, player->superWeaponY + 3);
        }
    }

    if(player->superWeaponFireTimer) {
        player->superWeaponFireTimer--;
    }

    if(player->superWeaponSeconds) {
        player->timeOut--;
        if(!player->timeOut){
            player->superWeaponSeconds--;
            if(player->superWeaponSeconds) {
                PrintU8Vertical(30, 0, player->superWeaponSeconds);
                player->timeOut = 60;
            } else {
                Fill(30, 0, 1, 17, 0);
            }
        }
    }

    if(player->scoreDelta) {
        player->score += player->scoreDelta;
        PrintU16Vertical(1, player->index ? 0 : 20, player->score, 50000, 1);
        player->scoreDelta = 0;
    }

    player->animTime++;
    if(player->animTime >= 12) {
        player->animTime = 0;
    }

    if(player->clawTime) {
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
