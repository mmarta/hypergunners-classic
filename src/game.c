#include "game.h"

u8 gameMode, gameLevel, gameSecondKills, gameKillTime, gameEnemyNextSpawnTime, gamePreviousKills;
u8 gameEnemyNextSpawnFactor, gameLevelSeconds, gameLevelTick, gameLevelUpTime, gameOverTime;

void GameReset() {
    gameMode = 1;
    gameOverTime = 0;
    gameLevel = 2;
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
    if(gameOverTime) {
        gameOverTime--;
        if(!gameOverTime) {
            gameMode = 0;
        }
        return;
    } else if(!players[0].active && !players[1].active) {
        gameOverTime = 150;
        PrintVerticalRAM(8, 18, "GAME OVER!");
        return;
    }

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
