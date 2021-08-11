#ifndef HGC_WHIPLINE_H
#define HGC_WHIPLINE_H

#include "defines.h"
#include "gfx.h"

#define WHIPLINE_W 1
#define WHIPLINE_H 2

typedef struct {
    u8 lane, x, y, active, grabbedTime, updateTime, usable;
} Whipline;

void WhiplineInit(Whipline *, u8);
u8 WhiplineIsCollidable(Whipline *);
void WhiplineUpdate(Whipline *);

#endif
