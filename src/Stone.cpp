#include "global.h"
#include "Stone.h"

bool Stone::update() {
    bool tmp = Object::update();
    
    if(isFall) {
        tmp = true;
        move(0,G_VELOCITY);
    }
    return tmp;
}

Stone::Stone(float _x,float _y,std::vector<ALLEGRO_BITMAP *>* _img) {
    type = STONE;
    move_dirc = NONE;

    ani_total_count = ANI_TOTAL_COUNT;
    ani_count = 0;
    ani_num = ANI_NUM[STONE];
    ani_image_idx = 0;

    x = _x;
    y = _y;

    width = CHUNK_WIDRH;
    height = CHUNK_HEIGHT;

    Image = _img;

    isFall = false;
}