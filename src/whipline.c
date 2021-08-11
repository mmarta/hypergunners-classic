#include "whipline.h"

void WhiplineDeactivate(Whipline *);

void WhiplineInit(Whipline *whipline, u8 lane) {
    if(whipline->active || !whipline->usable) {
        return;
    }

    whipline->lane = lane;
    whipline->x = LANE_BOTTOM_X - 1;
    whipline->y = (lane * 3) + 1;
    whipline->grabbedTime = 0;
    whipline->updateTime = 0;
    whipline->active = 1;

    DrawMap(whipline->x, whipline->y, mapWhipline[0]);
}

u8 WhiplineIsCollidable(Whipline *whipline) {
    return whipline->active && !whipline->grabbedTime;
}

void WhiplineUpdate(Whipline *whipline) {
    if(!whipline->active) {
        return;
    }

    u8 i = whipline->x, whipIndex = 0;

    whipline->updateTime++;
    if(whipline->updateTime >= 2) {
        whipline->updateTime = 0;

        if(!whipline->grabbedTime) {
            whipline->x--;
            if(whipline->x <= END_POINT_X) {
                WhiplineDeactivate(whipline);
                return;
            }
        } else {
            whipline->grabbedTime++;
            if(whipline->grabbedTime >= 13) {
                whipline->usable = 0;
                WhiplineDeactivate(whipline);
                return;
            }
        }
    } else {
        whipIndex = 2;
    }

    while(i < LANE_BOTTOM_X) {
        DrawMap(i, whipline->y, mapWhipline[whipIndex]);
        whipIndex++;
        if(whipIndex >= 4) {
            whipIndex = 0;
        }
        i++;
    }
}

void WhiplineDeactivate(Whipline *whipline) {
    whipline->active = 0;
    Fill(whipline->x, whipline->y, LANE_BOTTOM_X - whipline->x, WHIPLINE_H, 0);
}
