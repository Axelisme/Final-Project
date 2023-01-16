#ifndef MENU_H
#define MENU_H

#include "global.h"
#include "Interface.h"

class Menu: public Interface {
public:
    // update all object
    bool update();
    
    // load menu
    bool load_menu(int)
    {
        Start_menu = al_load_bitmap((IMAGE_PATH+"/Start_menu").c_str());
        Start_menu_L1 = al_load_bitmap((IMAGE_PATH+"/Start_menu_L1").c_str());
        Start_menu_L2 = al_load_bitmap((IMAGE_PATH+"/Start_menu_L2").c_str());
        Start_menu_music = al_load_bitmap((IMAGE_PATH+"/Start_menu_music").c_str());
        Start_menu_guide = al_load_bitmap((IMAGE_PATH+"/Start_menu_guide").c_str());
        Start_menu_exit = al_load_bitmap((IMAGE_PATH+"/Start_menu_exit").c_str());
        Game_menu = al_load_bitmap((IMAGE_PATH+"/Game_menu").c_str());
        Game_menu_repeat = al_load_bitmap((IMAGE_PATH+"/Game_menu").c_str());
        Game_menu_music = al_load_bitmap((IMAGE_PATH+"/Game_menu").c_str());
        Game_menu_guide = al_load_bitmap((IMAGE_PATH+"/Game_menu").c_str());
        Game_menu_back = al_load_bitmap((IMAGE_PATH+"/Game_menu").c_str());
        window_width = CHUNK_WIDTH;
        window_width = CHUNK_HEIGHT;
        width_ratio = 1;
        image_width = 0;
        image_height = 0;
        return true;
    };

    // process trigered by mouse
    GAME_STATE mouse_triger(int mouse){return GAME_MENU;}

    // constructor and deletor
    Menu(MENU_TYPE _type);
    ~Menu();

private:
    MENU_TYPE type;

    ALLEGRO_BITMAP *  Start_menu;
    ALLEGRO_BITMAP *  Start_menu_L1;
    ALLEGRO_BITMAP *  Start_menu_L2;
    ALLEGRO_BITMAP *  Start_menu_music;
    ALLEGRO_BITMAP *  Start_menu_guide;
    ALLEGRO_BITMAP *  Start_menu_exit;
    ALLEGRO_BITMAP *  Game_menu;
    ALLEGRO_BITMAP *  Game_menu_repeat;
    ALLEGRO_BITMAP *  Game_menu_music;
    ALLEGRO_BITMAP *  Game_menu_guide;
    ALLEGRO_BITMAP *  Game_menu_back;
};

#endif // MENU_H