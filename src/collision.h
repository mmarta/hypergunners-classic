#ifndef HGC_COLLISION_H
#define HGC_COLLISION_H

#include "defines.h"
#include "laser.h"
#include "whipline.h"
#include "player.h"
#include "enemy.h"
#include "game.h"

void CollisionLaserEnemy(Laser *, Enemy *, Player *);
void CollisionLasers(Laser *, Laser *);
void CollisionWhiplineEnemy(Whipline *, Enemy *, Player *);
void CollisionWhiplineLaser(Whipline *, Laser *);
void CollisionLaserPlayer(Laser *, Player *);
void CollisionPlayerEnemy(Player *, Enemy *);

#endif
