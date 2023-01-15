#include "Stone.h"

bool Stone::update() {
    bool tmp = Object::update();
    
    if(isFall) {
        tmp = true;
        move_object({1,0});
    }
    return tmp;
}

Stone::Stone(Pos _pos,ALLEGRO_BITMAP *_img):
       Object(_pos,_img,1,1)
{
    show_msg("Create stone begin");
    type = STONE;
    CanFall = true;
    move_dirc = NONE;

    ani_total_count = ANI_TOTAL_COUNT;
    ani_count = 0;
    ani_num = ANI_NUM;
    ani_image_idx = 0;

    pos = _pos;

    width = 1;
    height = 1;

    isFall = false;
    show_msg("Create stone done");
}