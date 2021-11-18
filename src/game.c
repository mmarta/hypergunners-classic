#include "game.h"

u8 gameLevel, gameSecondKills, gameKillTime, gameEnemyNextSpawnTime, gamePreviousKills;
u8 gameEnemySpawnWeight, gameEnemyNextSpawnFactor, gameLevelSeconds, gameLevelTick;

void GameReset() {
    gameLevel = 1;
    gameSecondKills = 0;
    gamePreviousKills = 4;
    gameKillTime = 0;
    gameEnemyNextSpawnFactor = 50;
    gameEnemyNextSpawnTime = rand() % 30 + gameEnemyNextSpawnFactor;
    gameEnemySpawnWeight = 0;
    gameLevelSeconds = 30;
    gameLevelTick = 60;
}

void GameAddKill() {
    gameSecondKills++;
}

void GameUpdateRank() {
    gameKillTime++;
    if(gameKillTime >= 120) {
        gameKillTime = 0;
        // PLACEHOLDER: Other rank calculations
        if(gameSecondKills > gamePreviousKills) {
            gameEnemyNextSpawnFactor = gameEnemyNextSpawnFactor > 10
                ? gameEnemyNextSpawnFactor - 5
                : 20;
        } else if(gameSecondKills < gamePreviousKills >> 1) {
            gameEnemyNextSpawnFactor = gameEnemyNextSpawnFactor < 100
                ? gameEnemyNextSpawnFactor + 5
                : 100;
        }

        gamePreviousKills = gameSecondKills;
        gameSecondKills = 0;
        PrintU8Vertical(2, 25, gameLevel);
        PrintU8Vertical(3, 25, gameEnemyNextSpawnFactor);
        PrintU8Vertical(4, 25, gameEnemySpawnWeight);
        PrintU8Vertical(5, 25, gamePreviousKills);
    }

    gameLevelTick--;
    if(!gameLevelTick) {
        gameLevelSeconds--;
        if(!gameLevelSeconds) {
            gameLevel++;
            gameEnemyNextSpawnFactor = gameEnemyNextSpawnFactor > 20 ? gameEnemyNextSpawnFactor - 5 : 20;
            PrintU8Vertical(2, 25, gameLevel);
            PrintU8Vertical(3, 25, gameEnemyNextSpawnFactor);
            PrintU8Vertical(4, 25, gameEnemySpawnWeight);
            PrintU8Vertical(5, 25, gamePreviousKills);
            gameLevelSeconds = 30;
        }
        gameLevelTick = 60;
    }
}

void GameDropRank() {
    gameKillTime = 0;
    gameSecondKills = 0;
    gamePreviousKills = 4;
    gameEnemyNextSpawnFactor = gameLevel > 17 ? 10 : 55 - (gameLevel * 5);
    PrintU8Vertical(2, 25, gameLevel);
    PrintU8Vertical(3, 25, gameEnemyNextSpawnFactor);
    PrintU8Vertical(4, 25, gameEnemySpawnWeight);
    PrintU8Vertical(5, 25, gamePreviousKills);
}

void GameSpawnUpdate() {
    gameEnemyNextSpawnTime--;
    if(!gameEnemyNextSpawnTime) {
        // Spawn enemy!
        EnemyInitNext(gameEnemySpawnWeight);

        gameEnemyNextSpawnTime = rand() % 30 + gameEnemyNextSpawnFactor;
    }
}
