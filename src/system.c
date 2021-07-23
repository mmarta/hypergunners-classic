#include "system.h"

int controls[TOTAL_CONTROLS];

void ReadControls() {
    controls[0] = ReadJoypad(0);
    controls[1] = ReadJoypad(1);
}
