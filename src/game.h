#ifndef HGC_GAME_H
#define HGC_GAME_H

#include "defines.h"
#include "gfx.h"
#include "background.h"
#include "player.h"
#include "enemy.h"
#include "collision.h"

#define SPAWN_CONSTANT 20
#define SPAWN_MIN_FACTOR 10
#define SPAWN_MAX_FACTOR 50
#define SPAWN_FACTOR_DELTA 5

typedef enum {
    TITLE,
    GAME,
    SCORE_ENTRY,
    DEMO
} GameMode;

// Rank items
extern u8 gameLevel, gameFourSecondKills, gameKillTime, gameEnemyNextSpawnTime;
extern u8 gameEnemySpawnWeight;

extern GameMode gameMode;

void GameReset();
void GameAddKill();
void GameUpdateRank();
void GameDropRank();
void GameSpawnUpdate();

void GameUpdateHighScores();

void UpdateGame();
void UpdateScoreEntry();

#endif
