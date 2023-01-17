#ifndef MENU_H
#define MENU_H

#include "global.h"
#include "Interface.h"

class Menu: public Interface {
public:
    GAME_STATE game_state;

    void draw() override;

    // update all object
    bool update() override;

    // process trigered by key
    GAME_STATE key_triger(int key);

    // process trigered by mouse
    GAME_STATE mouse_triger(int mouse){return GAME_MENU;}

    // constructor and deletor
    Menu(GAME_STATE _game_state);

private:
    ALLEGRO_BITMAP * ToImg(MENU_STATE stat);

    MENU_STATE menu_state = IN_MENU;

    ALLEGRO_BITMAP *  In_menu;
    ALLEGRO_BITMAP *  Start_menu;
    ALLEGRO_BITMAP *  Start_menu_level;
    ALLEGRO_BITMAP *  Start_menu_music;
    ALLEGRO_BITMAP *  Start_menu_guide;
    ALLEGRO_BITMAP *  Start_menu_exit;
    ALLEGRO_BITMAP *  Level_menu;
    ALLEGRO_BITMAP *  Level_menu_1;
    ALLEGRO_BITMAP *  Level_menu_2;
    ALLEGRO_BITMAP *  Level_menu_3;
    ALLEGRO_BITMAP *  Level_menu_4;
    ALLEGRO_BITMAP *  Level_menu_exit;
    ALLEGRO_BITMAP *  Guide;
};

#endif // MENU_H