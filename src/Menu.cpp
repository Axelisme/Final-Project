#include "Menu.h"

void Menu::draw() {
    // al_draw_scaled_bitmap(pic,0,0,al_get_bitmap_width(pic),al_get_bitmap_height(pic),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0)
    // al_clear_to_color(rgb)
    //al_draw_bitmap(Fix_Background_image,0,0,0);
    Interface::draw();
}

bool Menu::update() {
    return false;
}

GAME_STATE Menu::key_triger(int key) {
    if (game_state == GAME_LEVEL_PUASE)
    {
        if (key == ALLEGRO_KEY_ENTER || key == ALLEGRO_KEY_P)
        {
            return GAME_LEVEL;
        }
        else {return GAME_LEVEL_PUASE;}
    }
    else {
        
    }

    if(key == ALLEGRO_KEY_DOWN) {
        // show_msg("Key triger : switch to game menu");
        return GAME_MENU;
    } 
    if(key == ALLEGRO_KEY_UP) {
        // show_msg("Key triger : jump to next level");
        level_stat = NEXT;
        return GAME_LEVEL;
    } 
    if(key == ALLEGRO_KEY_ENTER) {
        // show_msg("Key triger : quit game");
        return GAME_TERMINATE;
    } 
    if(key_lock) {
        // show_msg("Key triger : key lock");
        snake->move_direction = NONE;
    }
    else {
        // show_msg("Key triger : move");
        snake->move_direction = KEY_TO_DIRC(key);
    }
    return GAME_LEVEL;
};

void Menu::set_key_lock() {

}

void Menu::update_key_lock() {

}

Menu::Menu(GAME_STATE _game_state):Interface("","") {
    game_state = _game_state;
    if (game_state == GAME_LEVEL)
    {
        menu_state = GUIDE;
        Guide = al_load_bitmap((MENUE_PATH+"/guide_menu").c_str());
    }
    else {
        menu_state = START_MENU;
        Start_menu = al_load_bitmap((MENUE_PATH+"/game_menu").c_str());
        Start_menu_level = al_load_bitmap((MENUE_PATH+"/game_menu_level").c_str());
        Start_menu_music = al_load_bitmap((MENUE_PATH+"/game_menu_music").c_str());
        Start_menu_guide = al_load_bitmap((MENUE_PATH+"/game_menu_guide").c_str());
        Start_menu_exit = al_load_bitmap((MENUE_PATH+"/game_menu_exit").c_str());
        Level_menu = al_load_bitmap((MENUE_PATH+"/level_in").c_str());
        Level_menu_1 = al_load_bitmap((MENUE_PATH+"/level_in1").c_str());
        Level_menu_2 = al_load_bitmap((MENUE_PATH+"/level_in2").c_str());
        Level_menu_3 = al_load_bitmap((MENUE_PATH+"/level_in3").c_str());
        Level_menu_4 = al_load_bitmap((MENUE_PATH+"/level_in4").c_str());
        Level_menu_exit = al_load_bitmap((MENUE_PATH+"/level_exit").c_str());
        Guide = al_load_bitmap((MENUE_PATH+"/guide_menu").c_str());
    }
    

}

Menu::~Menu() {
    
}