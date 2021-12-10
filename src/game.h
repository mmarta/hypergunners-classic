#ifndef HGC_GAME_H
#define HGC_GAME_H

#include "defines.h"
#include "gfx.h"
#include "player.h"
#include "enemy.h"

#define SPAWN_CONSTANT 20
#define SPAWN_MIN_FACTOR 10
#define SPAWN_MAX_FACTOR 50
#define SPAWN_FACTOR_DELTA 5

// Rank items
extern u8 gameMode, gameLevel, gameFourSecondKills, gameKillTime, gameEnemyNextSpawnTime;
extern u8 gameEnemySpawnWeight;

void GameReset();
void GameAddKill();
void GameUpdateRank();
void GameDropRank();
void GameSpawnUpdate();

#endif
