#include "game.h"

u8 gameLevel, gameSecondKills, gameKillTime, gameEnemyNextSpawnTime, gamePreviousKills;
u8 gameEnemyNextSpawnFactor, gameLevelSeconds, gameLevelTick, gameLevelUpTime, gameOverTime;

GameMode gameMode;

u16 gameHighScores[] = {
    100,
    80,
    60,
    40,
    20
};

char gameHighScoreInitials[] = {
    'R', 'B', 'T',
    'M', 'R', 'M',
    'S', 'L', 'M',
    'B', 'A', 'M',
    'D', 'M', 'M'
};

void GameInsertHighScore(u8, u16 *);
void GamePrintHighScores();
void GameClear();

void GameReset() {
    gameMode = GAME;
    gameOverTime = 0;
    gameLevel = 1;
    gameSecondKills = 0;
    gamePreviousKills = 4;
    gameKillTime = 0;
    gameEnemyNextSpawnFactor = SPAWN_MAX_FACTOR;
    gameEnemyNextSpawnTime = rand() % SPAWN_CONSTANT + gameEnemyNextSpawnFactor;
    gameLevelSeconds = 30;
    gameLevelTick = 60;

    PrintVerticalRAM(2, 18, "LEVEL");
    PrintU8Vertical(2, 9, gameLevel);

    PrintVerticalRAM(3, 17, "TIME");
    PrintU8Vertical(3, 10, gameLevelSeconds);
}

void GameAddKill() {
    gameSecondKills++;
}

void GameUpdateRank() {
    gameKillTime++;
    if(gameKillTime >= 240) {
        gameKillTime = 0;
        // PLACEHOLDER: Other rank calculations
        if(gameSecondKills > gamePreviousKills) {
            gameEnemyNextSpawnFactor = gameEnemyNextSpawnFactor > SPAWN_MIN_FACTOR
                ? gameEnemyNextSpawnFactor - SPAWN_FACTOR_DELTA
                : SPAWN_MIN_FACTOR;
        } else if(gameSecondKills < gamePreviousKills >> 1) {
            gameEnemyNextSpawnFactor = gameEnemyNextSpawnFactor < SPAWN_MAX_FACTOR
                ? gameEnemyNextSpawnFactor + SPAWN_FACTOR_DELTA
                : SPAWN_MAX_FACTOR;
        }

        gamePreviousKills = gameSecondKills;
        gameSecondKills = 0;
        PrintU8Vertical(3, 25, gameEnemyNextSpawnFactor);
        PrintU8Vertical(4, 25, gamePreviousKills);
    }

    gameLevelTick--;
    if(!gameLevelTick) {
        gameLevelSeconds--;
        PrintU8Vertical(3, 10, gameLevelSeconds);

        if(!gameLevelSeconds) {
            if(gameLevel < 255) {
                gameLevel++;
                gameLevelUpTime = 180;

                PrintU8Vertical(2, 9, gameLevel);
            }

            gameEnemyNextSpawnFactor = gameEnemyNextSpawnFactor > SPAWN_MIN_FACTOR
                ? gameEnemyNextSpawnFactor - SPAWN_FACTOR_DELTA
                : SPAWN_MIN_FACTOR;
            PrintU8Vertical(3, 25, gameEnemyNextSpawnFactor);
            PrintU8Vertical(4, 25, gamePreviousKills);
            gameLevelSeconds = 30;
        }
        gameLevelTick = 60;
    }

    if(gameLevelUpTime) {
        if(gameLevelUpTime % 60 == 0) {
            PrintVerticalRAM(6, 18, "LEVEL UP!!");
        } else if(gameLevelUpTime % 60 == 30) {
            Fill(6, 9, 1, 10, 0);
        }
        gameLevelUpTime--;
    }
}

void GameDropRank() {
    gameKillTime = 0;
    gameSecondKills = 0;
    gamePreviousKills = 4;
    gameEnemyNextSpawnFactor = gameLevel > 17
        ? SPAWN_MIN_FACTOR
        : SPAWN_MAX_FACTOR + SPAWN_FACTOR_DELTA - (gameLevel * SPAWN_FACTOR_DELTA);
    PrintU8Vertical(3, 25, gameEnemyNextSpawnFactor);
    PrintU8Vertical(4, 25, gamePreviousKills);
}

void GameSpawnUpdate() {
    gameEnemyNextSpawnTime--;
    if(!gameEnemyNextSpawnTime) {
        // Spawn enemy!
        EnemyInitNext(gameLevel);

        gameEnemyNextSpawnTime = rand() % SPAWN_CONSTANT + gameEnemyNextSpawnFactor;
    }
}

void GameClear() {
    u8 i;

    // Deactivate all baddies
    i = ENEMY_LASER_COUNT;
    while(i--) {
        EnemyLaserDeactivate(&enemyLasers[i]);
    }

    i = ENEMY_COUNT;
    while(i--) {
        EnemyDeactivate(&enemies[i]);
    }

    // Clear the screen
    Fill(0, 0, 32, 28, 0);
}

void GameInsertHighScore(u8 pos, u16 *score) {
    if(pos >= 5) {
        return;
    }

    u8 i = HIGH_SCORE_COUNT - 1, iOffset;
    while(i > pos) {
        iOffset = i * 3;
        gameHighScores[i] = gameHighScores[i - 1];
        gameHighScoreInitials[iOffset] = gameHighScoreInitials[iOffset - 3];
        gameHighScoreInitials[iOffset + 1] = gameHighScoreInitials[iOffset - 2];
        gameHighScoreInitials[iOffset + 2] = gameHighScoreInitials[iOffset - 1];
        i--;
    }

    gameHighScores[pos] = *score;
    gameHighScoreInitials[pos * 3] = 'A';
    gameHighScoreInitials[pos * 3 + 1] = ' ';
    gameHighScoreInitials[(pos * 3) + 2] = ' ';
}

void GameUpdateHighScores() {
    u8 j, pos;
    for(u8 i = 0; i < PLAYER_COUNT; i++) {
        j = HIGH_SCORE_COUNT;
        pos = 5;
        players[i].scorePos = pos;
        while(j--) {
            if(players[i].score > gameHighScores[j]) {
                pos = j;
                if(!j) {
                    GameInsertHighScore(pos, &players[i].score);
                    players[i].scorePos = pos;
                    if(i && players[i].scorePos <= players[i - 1].scorePos) {
                        players[i - 1].scorePos--;
                    }
                    break;
                }
            } else {
                GameInsertHighScore(pos, &players[i].score);
                players[i].scorePos = pos;
                if(i && players[i].scorePos <= players[i - 1].scorePos) {
                    players[i - 1].scorePos--;
                }
                break;
            }
        }
    }
}

void GamePrintHighScores() {
    u8 x;
    PrintVerticalRAM(6, 19, "TODAY'S BEST");
    for(u8 i = 0; i < HIGH_SCORE_COUNT; i++) {
        x = 8 + (i << 1);
        PrintU16Vertical(x, 6, gameHighScores[i], 50000, 1);
        PrintVerticalChar(x, 21, gameHighScoreInitials[(i * 3)]);
        PrintVerticalChar(x, 20, gameHighScoreInitials[(i * 3) + 1]);
        PrintVerticalChar(x, 19, gameHighScoreInitials[(i * 3) + 2]);

        if(players[0].scorePos == i) {
            PrintVerticalChar(x, 23, '^');
        } else if(players[1].scorePos == i) {
            PrintVerticalChar(x, 23, '_');
        }
    }
}

void UpdateScoreEntry() {
    u8 j, x, exitEntry = 1;

    for(u8 i = 0; i < PLAYER_COUNT; i++) {
        if(players[i].scorePos >= 5) {
            continue;
        }

        j = (players[i].scorePos * 3) + players[i].letterEntryIndex;
        x = 8 + (players[i].scorePos << 1);

        if(controls[i] & BTN_LEFT || controls[i] & BTN_RIGHT) {
            if(controls[i] & BTN_LEFT) {
                if(!players[i].leftStick) {
                    gameHighScoreInitials[j]--;
                    if(gameHighScoreInitials[j] == 64) {
                        gameHighScoreInitials[j] = 32;
                    } else if(gameHighScoreInitials[j] == 31) {
                        gameHighScoreInitials[j] = 90;
                    }
                }

                players[i].leftStick++;
                if(players[i].leftStick >= 8) {
                    players[i].leftStick = 0;
                }
                players[i].rightStick = 0;
            } else {
                if(!players[i].rightStick) {
                    gameHighScoreInitials[j]++;
                    if(gameHighScoreInitials[j] == 91) {
                        gameHighScoreInitials[j] = 32;
                    } else if(gameHighScoreInitials[j] == 33) {
                        gameHighScoreInitials[j] = 65;
                    }
                }

                players[i].rightStick++;
                if(players[i].rightStick >= 8) {
                    players[i].rightStick = 0;
                }
                players[i].leftStick = 0;
            }
            PrintVerticalChar(x, 21 - players[i].letterEntryIndex, gameHighScoreInitials[j]);
        } else {
            players[i].leftStick = 0;
            players[i].rightStick = 0;
        }

        if(controls[i] & BTN_A) {
            if(!players[i].fireButton && players[i].letterEntryIndex < 3) {
                players[i].letterEntryIndex++;
                if(players[i].letterEntryIndex < 3) {
                    // Show the next "A" when the letter is entered
                    gameHighScoreInitials[j + 1] = 'A';
                    PrintVerticalChar(x, 21 - players[i].letterEntryIndex, gameHighScoreInitials[j + 1]);
                }
                players[i].fireButton = 1;
            }
        } else {
            players[i].fireButton = 0;
        }

        // Player not finished yet?
        if(players[i].letterEntryIndex < 3) {
            exitEntry = 0;
        }
    }

    // Both players finished entering their name?
    if(exitEntry) {
        gameMode = TITLE;
        PrintVerticalRAM(28, 16, "DONE");
    }
}

// Main Game Update Code!

void UpdateGame() {
    u8 i, j, k, t = 0, playerCollisionCondition;

    // Collision first
    i = ENEMY_COUNT;
    while(i--) {
        j = 0;
        //playerCollisionCondition = t ? j < PLAYER_COUNT : j != 0xff;

        while(j < PLAYER_COUNT) {
            k = 0;
            while(k < PLAYER_LASER_COUNT) {
                CollisionLaserEnemy(&players[j].lasers[k], &enemies[i], &players[j]);
                k++;
            }

            k = 0;
            while(k < PLAYER_EXTRA_LASER_COUNT) {
                CollisionLaserEnemy(&players[j].extraLasers[k], &enemies[i], &players[j]);
                k++;
            }

            CollisionWhiplineEnemy(&players[j].whipline, &enemies[i], &players[j]);

            CollisionPlayerEnemy(&players[j], &enemies[i]);
            j++;

            /*if(t) {
                j++;
                playerCollisionCondition = j < PLAYER_COUNT;
            } else {
                j--;
                playerCollisionCondition = j != 0xff;
            }*/
        }
    }

    i = ENEMY_LASER_COUNT;
    while(i--) {
        j = 0;
        //playerCollisionCondition = t ? j < PLAYER_COUNT : j != 0xff;

        while(j < PLAYER_COUNT) {
            k = 0;
            while(k < PLAYER_LASER_COUNT) {
                CollisionLasers(&players[j].lasers[k], &enemyLasers[i]);
                k++;
            }

            k = 0;
            while(k < PLAYER_EXTRA_LASER_COUNT) {
                CollisionLasers(&players[j].extraLasers[k], &enemyLasers[i]);
                k++;
            }

            CollisionWhiplineLaser(&players[j].whipline, &enemyLasers[i]);

            CollisionLaserPlayer(&enemyLasers[i], &players[j]);
            j++;

            /*if(t) {
                j++;
                playerCollisionCondition = j < PLAYER_COUNT;
            } else {
                j--;
                playerCollisionCondition = j != 0xff;
            }*/
        }
    }

    PlayerInput(&players[0]);
    PlayerInput(&players[1]);

    // Game Over ?
    if(gameOverTime) {
        gameOverTime--;
        if(!gameOverTime) {
            GameClear();
            GameUpdateHighScores();
            GamePrintHighScores();
            if(players[0].scorePos < 5 || players[1].scorePos < 5) {
                gameMode = SCORE_ENTRY;
            } else {
                gameMode = TITLE;
            }
            return;
        }
    } else if(!players[0].active && !players[1].active) {
        gameOverTime = 150;
        PrintVerticalRAM(8, 18, "GAME OVER!");
    }

    // Update spawn time and see if we generate a new enemy
    GameSpawnUpdate();

    BackgroundUpdate();
    GameUpdateRank();

    i = ENEMY_LASER_COUNT;
    while(i--) {
        EnemyLaserUpdate(&enemyLasers[i]);
    }

    i = ENEMY_COUNT;
    while(i--) {
        EnemyUpdate(&enemies[i]);
    }

    if(t) {
        PlayerUpdate(&players[1]);
        PlayerUpdate(&players[0]);
    } else {
        PlayerUpdate(&players[0]);
        PlayerUpdate(&players[1]);
    }

    t++;
    t = t % 2;
}
