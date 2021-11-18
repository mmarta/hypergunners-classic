#ifndef HGC_GAME_H
#define HGC_GAME_H

#include "defines.h"
#include "gfx.h"
#include "player.h"
#include "enemy.h"

// Rank items
extern u8 gameLevel, gameFourSecondKills, gameKillTime, gameEnemyNextSpawnTime;
extern u8 gameEnemySpawnWeight;

void GameReset();
void GameAddKill();
void GameUpdateRank();
void GameDropRank();
void GameSpawnUpdate();

#endif
