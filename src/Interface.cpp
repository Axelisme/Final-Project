#include "Interface.h"

void Interface::draw() {
    if(SIMPLY_DISPLAY){
        al_clear_to_color(BLACK);
    }
    else{
    al_clear_to_color(BLACK);
    al_draw_bitmap(backgroundImage, 0, 0, 0);
    start_sound();
    }
}

bool Interface::update() {
    return true;
}

Interface::Interface(string sound_path="",string image_path="") {
    // load sound
    if(!sound_path.empty()) {
        sample = al_load_sample(sound_path.c_str());
        backgroundSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
    }
    else raise_warn("no sound path given");

    // load background image
    if(!image_path.empty()) {
        backgroundImage = al_load_bitmap(image_path.c_str());
    }
    else raise_warn("no image path given");
}

void Interface::destroy_Interface() {
    al_destroy_sample_instance(backgroundSound);
    al_destroy_sample(sample);
    al_destroy_bitmap(backgroundImage);
}

Interface::~Interface() {
    destroy_Interface();
}