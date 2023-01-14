#include "Interface.h"

void Interface::draw() {
    al_clear_to_color(BLACK);
    al_draw_bitmap(backgroundImage, 0, 0, 0);
}

Interface::Interface(string sound_path="",string image_path="") {
    if(!sound_path.empty()) {
        sample = al_load_sample(sound_path.c_str());
        backgroundSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
    }
    if(!image_path.empty()) {
        backgroundImage = al_load_bitmap(image_path.c_str());
    }
}

Interface::~Interface() {
    al_destroy_sample_instance(backgroundSound);
    al_destroy_sample(sample);
    al_destroy_bitmap(backgroundImage);
}