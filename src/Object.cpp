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
    if(SIMPLY_DISPLAY) {
        al_draw_rectangle((pos.second - width/2 )*CHUNK_WIDTH,
                          (pos.first  - height/2)*CHUNK_HEIGHT,
                          (pos.second + width/2 )*CHUNK_WIDTH,
                          (pos.first  + height/2)*CHUNK_HEIGHT,
                          SIMPLE_COLOR_LIST[type],
                          0);
    } 
    else
    {
        if(Image==nullptr) {
            raise_warn("try to draw null object"); 
            return;
        }
        float Image_width = al_get_bitmap_width(Image);
        float Image_height = al_get_bitmap_height(Image);
        Pos pos = ConvertIdx(ani_image_idx);
        al_draw_scaled_bitmap(Image,
                            pos.first,pos.second,
                            Image_width/2,
                            Image_height/2,
                            (pos.second-width/2)*CHUNK_WIDTH,
                            (pos.first-height/2)*CHUNK_HEIGHT,
                            width*CHUNK_WIDTH,
                            height*CHUNK_HEIGHT,
                            0
                            );
    }
}

bool Object::update() {
    if((++ani_count)%ani_total_count == 0) {
        ani_image_idx = (++ani_image_idx)%ani_num;
        return true;
    }
    return false;
}
