#include "Interface.h"

void Interface::draw() {
    if(SIMPLY_DISPLAY){
        al_clear_to_color(PINK);
    }
    else{
        al_clear_to_color(WRITE);
        start_sound();
        const float sx = CHUNK_WIDTH*width_ratio*(window_center.second - window_width/2);
        const float sy = 0;
        const float sw = CHUNK_WIDTH*(width_ratio*window_width);
        const float sh = CHUNK_HEIGHT*image_height;
        const float dx = 0;
        const float dy = 0;
        const float dw = CHUNK_WIDTH*window_width;
        const float dh = CHUNK_HEIGHT*window_height;
        //al_draw_scaled_bitmap(backgroundImage,sx,sy,sw,sh,dx,dy,dw,dh,0);
    }
}

bool Interface::update() {
    return false;
}

Interface::Interface(string sound_path="",string image_path="") {
    show_msg("Create Interface begin");
    // load sound
    if(!sound_path.empty()) {
        sample = al_load_sample(sound_path.c_str());
        if(sample==nullptr) backgroundSound = nullptr;\
        else {
            backgroundSound = al_create_sample_instance(sample);
            al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
        }
    }
    else raise_warn("no sound path given");

    window_width = CHUNK_W_NUM;
    window_height = CHUNK_H_NUM;
    width_ratio = 1;
    image_width = 0;
    image_height = 0; 

    // load background image
    if(!image_path.empty()) {
        backgroundImage = al_load_bitmap(image_path.c_str());
        if(backgroundImage==nullptr) {
            raise_err("Can't not load background image because invalid path");
        }
        image_width =  al_get_bitmap_width(backgroundImage)/CHUNK_WIDTH;
        image_height = al_get_bitmap_height(backgroundImage)/CHUNK_HEIGHT;
        width_ratio = image_width/SEE_MAP_WIDTH;
    }
    else raise_warn("no image path given");
    show_msg("Create interface done");
}

void Interface::destroy_Interface() {
    show_msg("Destroy interface begin");
    al_destroy_sample_instance(backgroundSound);
    al_destroy_sample(sample);
    al_destroy_bitmap(backgroundImage);
    backgroundSound = nullptr;
    sample = nullptr;
    backgroundImage = nullptr;

    show_msg("Destroy interface done");
}

Interface::~Interface() {
    show_msg("Delete interface begin");
    destroy_Interface();
    show_msg("Delete interface done");
}