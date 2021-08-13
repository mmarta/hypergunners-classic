#ifndef HGC_COLLISION_H
#define HGC_COLLISION_H

#include "defines.h"
#include "laser.h"
#include "whipline.h"
#include "player.h"
#include "enemy.h"

void CollisionLaserEnemy(Laser *, Enemy *, Player *);
void CollisionWhiplineEnemy(Whipline *, Enemy *, Player *);

#endif
