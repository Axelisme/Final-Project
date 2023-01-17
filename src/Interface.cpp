#include "Interface.h"
#include "GameWindow.h"

void Interface::draw() {
    al_clear_to_color(al_map_rgb(light,light,light));
    float sx = CHUNK_WIDTH*width_ratio1*(window_center.second-window_width/2-SEE_MAP_LEFT);
    float sy = 0;
    float sw = CHUNK_WIDTH*(window_width);
    float sh = al_get_bitmap_height(backgroundImage1);
    float dx = 0;
    float dy = 0;
    float dw = CHUNK_WIDTH*window_width;
    float dh = CHUNK_HEIGHT*window_height;
    if(SHOW_BACK_FOG) al_draw_scaled_bitmap(backgroundImage1,sx,sy,sw,sh,dx,dy,dw,dh,0);
    sx = CHUNK_WIDTH*width_ratio2*(window_center.second-window_width/2-SEE_MAP_LEFT);
    sy = 0;
    sw = CHUNK_WIDTH*(window_width);
    sh = al_get_bitmap_height(backgroundImage2);
    dx = 0;
    dy = 0;
    dw = CHUNK_WIDTH*window_width;
    dh = CHUNK_HEIGHT*window_height;
    al_draw_scaled_bitmap(backgroundImage2,sx,sy,sw,sh,dx,dy,dw,dh,0);
}

bool Interface::update() {
    down_then_lift();
    return false;
}

Interface::Interface(string sound_path="",string back1path="",string back2path="") {
    show_msg("Create Interface begin");
    // load sound
    if(!sound_path.empty()) {
        sample = al_load_sample(sound_path.c_str());
        if(sample==nullptr) backgroundSound = nullptr;
        else {
            backgroundSound = al_create_sample_instance(sample);
            al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
        }
    }
    else raise_warn("no sound path given");

    window_width = CHUNK_W_NUM;
    window_height = CHUNK_H_NUM;
    width_ratio1 = 1;
    image_width1 = 0;
    image_height1 = 0; 
    width_ratio2 = 1;
    image_width2 = 0;
    image_height2 = 0; 

    // load background1 image
    if(!back1path.empty()) {
        backgroundImage1 = al_load_bitmap(back1path.c_str());
        if(backgroundImage1==nullptr) {
            raise_err("Can't not load background image because invalid path");
        }
        image_width1 =  al_get_bitmap_width(backgroundImage1)/CHUNK_WIDTH;
        image_height1 = al_get_bitmap_height(backgroundImage1)/CHUNK_HEIGHT;
        width_ratio1 = (image_width1-window_width)/(SEE_MAP_RIGHT-SEE_MAP_LEFT-window_width);
    }
    else raise_warn("no image path given for background 1");

    // load background2 image
    if(!back2path.empty()) {
        backgroundImage2 = al_load_bitmap(back2path.c_str());
        if(backgroundImage2==nullptr) {
            raise_err("Can't not load background image because invalid path");
        }
        image_width2 =  al_get_bitmap_width(backgroundImage2)/CHUNK_WIDTH;
        image_height2 = al_get_bitmap_height(backgroundImage2)/CHUNK_HEIGHT;
        width_ratio2 = (image_width2-window_width)/(SEE_MAP_RIGHT-SEE_MAP_LEFT-window_width);
    }
    else raise_warn("no image path given for background 2");


    show_msg("Create interface done");
}

void Interface::down_then_lift() {
    if(!stay){
        if(up_or_down){
            light = (light+1)%255;
        }
        else {
            --light;
            if(light<=0) {
                up_or_down=true;
                light = 0;
            }
        }
        if(light==255) stay=true;
    }
}


void Interface::destroy_Interface() {
    show_msg("Destroy interface begin");
    al_destroy_sample_instance(backgroundSound);
    al_destroy_sample(sample);
    al_destroy_bitmap(backgroundImage1);
    al_destroy_bitmap(backgroundImage2);
    backgroundSound = nullptr;
    sample = nullptr;
    backgroundImage1 = nullptr;
    backgroundImage2 = nullptr;

    show_msg("Destroy interface done");
}

Interface::~Interface() {
    show_msg("Delete interface begin");
    destroy_Interface();
    show_msg("Delete interface done");
}