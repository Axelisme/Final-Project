#ifndef MENU_H
#define MENU_H

#include "global.h"
#include "Interface.h"

class Menu: public Interface {
public:
    void draw() override;

    // update all object
    bool update();

    // process trigered by key
    GAME_STATE key_triger(int key);

    //set key lock
    void set_key_lock() {
        //show_msg("key lock");
        key_lock = true;
        key_lock_count=0;
    }

    //update key lock
    void update_key_lock() {
        if(key_lock_num==0 || key_lock && (++key_lock_count%key_lock_num == 0)) {
            //show_msg("key unlock");
            key_lock = false;
            key_lock_count = 0;
        }
    }

    // process trigered by mouse
    GAME_STATE mouse_triger(int mouse){return GAME_MENU;}

    // constructor and deletor
    Menu(MENU_TYPE _type);
    ~Menu();

private:
    MENU_TYPE type;

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
    

    bool key_lock = false;
    int key_lock_count = 0;
    const int key_lock_num = KEY_LOCK_NUM;

};

#endif // MENU_H