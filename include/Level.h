#ifndef LEVEL_H
#define LEVEL_H

#include "Draw.h"

class Level: Draw {
public:
    void draw();
    void update();

    Level(int l=1);
};

#endif // LEVEL_H