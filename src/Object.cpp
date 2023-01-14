#include "Object.h"


void Object::draw() {
    if(Image==nullptr) {
        raise_warn("try to draw null object"); 
        return;
    }
    ALLEGRO_BITMAP * img = (*Image)[ani_image_idx];
    al_draw_scaled_bitmap(img,
                          0,0,
                          al_get_bitmap_width(img),
                          al_get_bitmap_height(img),
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

