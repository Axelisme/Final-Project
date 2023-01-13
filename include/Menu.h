#ifndef MENU_H
#define MENU_H

#include "Draw.h"

enum MENU_TYPE {
    START,
    SELECT_LEVEL,
    IN_GAME
};

class Menu: Draw {
public:
    MENU_TYPE state;
    void draw();
    void update();
};

#endif // MENU_H