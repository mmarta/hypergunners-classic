#ifndef HGC_DEFINES_H
#define HGC_DEFINES_H

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <uzebox.h>

#define SPLIT_POINT_X 20
#define END_POINT_X 17
#define LANE_BOTTOM_X 28

#define CALC_Y_FROM_LANE(lane) (((8 - lane) * 3) + 1)

#endif
