#include "Stone.h"

#include <iostream>

bool Stone::update() {
    Object::update();
    
    if(move_dirc != NONE) {
        show_msg("Stone move begin");
        move_object(DIRC_TO_POS(move_dirc));
        move_dirc = NONE;
        show_msg("Stone move done");
    }
    return true;
}

Stone::Stone(Pos _pos,ALLEGRO_BITMAP *_img):
       Object(_pos,STONE,_img,1,1)
{
    show_msg("Create stone begin");
    type = STONE;
    move_dirc = NONE;

    ani_total_count = ANI_TOTAL_COUNT;
    ani_count = 0;
    ani_num = ANI_NUM;
    ani_image_idx = 0;

    pos = _pos;

    width = 1;
    height = 1;

    show_msg("Create stone done");
}