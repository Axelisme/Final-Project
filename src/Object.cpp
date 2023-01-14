#include "Object.h"

Pos ConvertIdx(int idx) {
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
    float Image_width = al_get_bitmap_width(Image);
    float Image_height = al_get_bitmap_height(Image);
    Pos pos = ConvertIdx(ani_image_idx);
    al_draw_scaled_bitmap(Image,
                          pos.first,pos.second,
                          Image_width/2,
                          Image_height/2,
                          (x-width/2)*CHUNK_WIDRH,
                          (y-height/2)*CHUNK_HEIGHT,
                          width*CHUNK_WIDRH,
                          height*CHUNK_HEIGHT,
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

