#include "global.h"
#include "Level.h"

void Level::draw() {
    Interface::draw();

    for(auto &o:object) {
        o->draw();
    }
    
    snake->draw();
}

inline bool Level::is(int _y,int _x,OBJ_TYPE T) {
        return map.at(_y).at(_x) == T;
}

// update all object
bool Level::update() {
    bool tmp = false;
    if((key_lock && ++key_lock_count)%key_lock_num == 0) {
        key_lock = false;
        tmp = true;
    }
    
    for(auto &ob:object) {
        switch(ob->type) {
            case STONE: {
                int x = int(ob->getx());
                int y = int(ob->gety());
                if(is(y+1,x,AIR)) {
                    ob->move_dirc = DOWN;
                    if(map[y][x]!=STONE) raise_warn("some thing mismatch about map"); 
                    map[y][x] = AIR;
                    ob->update();
                    ob->move_dirc = NONE;
                    map.at(y+1).at(x) = STONE;
                    tmp = true;
                }
                else {
                    ob->move_dirc = NONE;
                }
                break;
            }
            default: raise_warn("try to update unknown type");
        }
    }
    
     
    for(auto &b:snake->body) {
        int x = b->getx();
        int y = b->gety();
        if(is(y,x,AIR)){}
    }
    


    return tmp;
}

// process trigered by key
GAME_STATE Level::key_triger(int key) {
    if(key == ALLEGRO_KEY_P) return GAME_MENU; 
    if(key == ALLEGRO_KEY_R) {
        reset();
        return GAME_LEVEL;
    }
    if(key_lock) return GAME_LEVEL;
    if(key>=ALLEGRO_KEY_LEFT && key <= ALLEGRO_KEY_DOWN) {
        snake->move_direction = static_cast<MOVE_DIRCTION> (key - ALLEGRO_KEY_LEFT);
        return GAME_LEVEL;
    }
    else {
        raise_warn("Unknown key");
        return GAME_LEVEL;
    }
}

// load level
bool Level::load_level(int) {return true;}

// reset
void Level::reset() {}

// constructor and deletor
Level::Level(int i):Interface(MUSIC_PATH+"level_bgm.ogg",IMAGE_PATH+"background.jpg") {
    level_idx = i;
    Ground_image = al_load_bitmap((IMAGE_PATH+"/ground.png").c_str());
    Stone_image = al_load_bitmap((IMAGE_PATH+"/stone.png").c_str());
    Apple_image = al_load_bitmap((IMAGE_PATH+"/apple.png").c_str());
    Snake_head_image = al_load_bitmap((IMAGE_PATH+"/head.png").c_str());
    Snake_body_image = al_load_bitmap((IMAGE_PATH+"/body.png").c_str());

    key_lock = false;
    key_lock_count =0;
    
    load_level(i);
}

Level::~Level() {
    al_destroy_bitmap(Ground_image);
    al_destroy_bitmap(Stone_image);
    al_destroy_bitmap(Apple_image);
    al_destroy_bitmap(Snake_head_image);
    al_destroy_bitmap(Snake_body_image);

    delete snake;
    for(auto &o:object) delete o;
}