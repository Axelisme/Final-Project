#include "Object.h"

Pos Object::ConvertIdx(int idx) {
    switch(idx) {
        case 0: return std::make_pair(0.0,0.0);
        case 1: return std::make_pair(0.0,0.5);
        case 2: return std::make_pair(0.5,0.0);
        case 3: return std::make_pair(0.5,0.5);
        default: {
            raise_warn("want to convert invalid idx");
            return {0.0,0.0};
        }
    }
}

void Object::draw() {
    if(Image==nullptr) {
        raise_warn("try to draw null object"); 
        return;
    }

    al_draw_scaled_bitmap(Image,
                            0,0,
                            al_get_bitmap_width(Image),al_get_bitmap_height(Image),
                            CHUNK_WIDTH *(pos.second - window_x - 1.5),
                            CHUNK_HEIGHT*(pos.first  - window_y - 1.5),
                            3*CHUNK_WIDTH , 3*CHUNK_HEIGHT,
                            0
                            );
}

bool Object::update() {
    if((++ani_count)%ani_total_count == 0) {
        ani_image_idx = (++ani_image_idx)%ani_num;
        return true;
    }
    return false;
}

Object::Object(Pos _pos,OBJ_TYPE T,ALLEGRO_BITMAP* _img,float _w,float _h) {
    pos = _pos;
    type = T;

    image_width = 0;
    image_height = 0;

    rotate_angle = 0;

    Image = _img;
    if(Image!=nullptr) {
        raise_warn("load object image fail");
        image_width = al_get_bitmap_width(Image)/CHUNK_WIDTH;
        image_height = al_get_bitmap_height(Image)/CHUNK_HEIGHT;
    }
    
    width = _w;
    height = _h;
}