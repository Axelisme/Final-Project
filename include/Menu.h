#ifndef MENU_H
#define MENU_H

#include "global.h"
#include "Interface.h"

class Menu: public Interface {
public:
    // update all object
    bool update();
    
    // process trigered by mouse
    GAME_STATE mouse_triger(int mouse){return GAME_MENU;}

    // constructor and deletor
    Menu(MENU_TYPE _type);
    ~Menu();

private:
    MENU_TYPE type;
};

#endif // MENU_H