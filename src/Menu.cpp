#include "Menu.h"

ALLEGRO_BITMAP * Menu::ToImg(MENU_STATE stat) {
    switch(stat) {
        case IN_MENU:
            return In_menu;
        case START_MENU:
            return Start_menu;
        case START_MENU_LEVEL:
            return Start_menu_level;
        case START_MENU_MUSIC:
            return Start_menu_music;
        case START_MENU_GUID:
            return Start_menu_guide;
        case START_MENU_EXIT:
            return Start_menu_exit;
        case LEVEL_MENU:
            return Level_menu;
        case LEVEL_MENU_1:
            return Level_menu_1;
        case LEVEL_MENU_2:
            return Level_menu_2;
        case LEVEL_MENU_3:
            return Level_menu_3;
        case LEVEL_MENU_4:
        case LEVEL_MENU_EXIT:
            return Level_menu_exit;
        case GUIDE:
            return Guide;
        
        default:
            raise_warn("Unknown menu draw issue");
            return In_menu;
    }
}

void Menu::draw() {
    ALLEGRO_BITMAP * img = ToImg(menu_state);
    al_draw_scaled_bitmap(img,
                          0,0,
                          al_get_bitmap_width(img),
                          al_get_bitmap_height(img),
                          0,0,
                          DISPLAY_WIDTH,DISPLAY_HEIGHT,
                          0);
    al_flip_display();
}

// bool Menu::update(){return true;}

GAME_STATE Menu::key_triger(int key) {
    if (menu_state == IN_MENU)
    {
        menu_state = START_MENU;
        return GAME_MENU;
    }
    else if (game_state == GAME_LEVEL_PUASE)
    {
        if (key == ALLEGRO_KEY_ENTER || key == ALLEGRO_KEY_P)
        {
            return GAME_LEVEL;
        }
        else {return GAME_LEVEL_PUASE;}
    }
    else {
        if(key == ALLEGRO_KEY_DOWN && (menu_state == START_MENU_EXIT || menu_state == LEVEL_MENU_EXIT || menu_state == GUIDE)) {
            show_msg("Key triger : at the bottom of menu");
            return GAME_MENU;
        }
        if(key == ALLEGRO_KEY_DOWN && (menu_state != START_MENU_EXIT && menu_state != LEVEL_MENU_EXIT && menu_state != GUIDE)) {
            show_msg("Key triger : menu select go down");
            menu_state = MENU_STATE(((int)menu_state)+1);
            return GAME_MENU;
        } 
        if(key == ALLEGRO_KEY_UP && (menu_state == START_MENU || menu_state == LEVEL_MENU || menu_state || GUIDE)) {
            show_msg("Key triger : at the top of menu");
            return GAME_LEVEL;
        } 
        if(key == ALLEGRO_KEY_UP && (menu_state != START_MENU && menu_state != LEVEL_MENU && menu_state != GUIDE)) {
            show_msg("Key triger : menu select go up");
            menu_state = MENU_STATE(((int)menu_state)+1);
            return GAME_MENU;
        } 
        if(key == ALLEGRO_KEY_ENTER) {
            switch (menu_state)
            {
            case START_MENU_LEVEL:
                menu_state = LEVEL_MENU;
                return GAME_MENU;
                break;
            case START_MENU_MUSIC:
                /* code */
                return GAME_MENU;
                break;
            case START_MENU_GUID:
                menu_state = GUIDE;
                return GAME_MENU;
                break;
            case START_MENU_EXIT:
                /* code */
                break;
            case LEVEL_MENU_1:
                /* code */
                return GAME_LEVEL;
                break;
            case LEVEL_MENU_2:
                /* code */
                return GAME_LEVEL;
                break;
            case LEVEL_MENU_3:
                /* code */
                return GAME_LEVEL;
                break;
            case LEVEL_MENU_4:
                /* code */
                return GAME_LEVEL;
                break;
            case LEVEL_MENU_EXIT:
                menu_state = START_MENU;
                return GAME_MENU;
                break;
            case GUIDE:
                menu_state = START_MENU;
                return GAME_MENU;
                break;

            default:
                return GAME_MENU;
                break;
            }
            // show_msg("Key triger : quit game");
            // return GAME_TERMINATE;
        } 
        else {
            return GAME_MENU;
        }
    }
    return GAME_MENU;
}

bool Menu::update() {
    draw();
    return true;
}

Menu::Menu(GAME_STATE _game_state):Interface("","","") {
    game_state = _game_state;
    if (game_state == GAME_LEVEL)
    {
        menu_state = GUIDE;
        Guide = al_load_bitmap((MENUE_PATH+"/guide_menu.png").c_str());
    }
    else {
        In_menu = al_load_bitmap((MENUE_PATH+"/menu.png").c_str());
        Start_menu = al_load_bitmap((MENUE_PATH+"/game_menu.png").c_str());
        Start_menu_level = al_load_bitmap((MENUE_PATH+"/game_menu_level.png").c_str());
        Start_menu_music = al_load_bitmap((MENUE_PATH+"/game_menu_music.png").c_str());
        Start_menu_guide = al_load_bitmap((MENUE_PATH+"/game_menu_guide.png").c_str());
        Start_menu_exit = al_load_bitmap((MENUE_PATH+"/game_menu_exit.png").c_str());
        Level_menu = al_load_bitmap((MENUE_PATH+"/level_in.png").c_str());
        Level_menu_1 = al_load_bitmap((MENUE_PATH+"/level_in1.png").c_str());
        Level_menu_2 = al_load_bitmap((MENUE_PATH+"/level_in2.png").c_str());
        Level_menu_3 = al_load_bitmap((MENUE_PATH+"/level_in3.png").c_str());
        Level_menu_4 = al_load_bitmap((MENUE_PATH+"/level_in4.png").c_str());
        Level_menu_exit = al_load_bitmap((MENUE_PATH+"/level_exit.png").c_str());
        Guide = al_load_bitmap((MENUE_PATH+"/guide_menu.png").c_str());
        if (!(In_menu && Start_menu && Start_menu_level && Start_menu_music && Start_menu_guide &&
            Start_menu_exit && Level_menu && Level_menu_1 && Level_menu_2 && Level_menu_3 &&
            Level_menu_4 && Level_menu_exit && Guide))
        {
            raise_warn("menu image missing");
        }
        
    }
    

}

Menu::~Menu() {
    
}