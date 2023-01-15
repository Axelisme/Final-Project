#ifndef INTERFACCE_H
#define INTERFACCE_H

#include "global.h"
#include "Object.h"
#include <vector>
#include <string>

using namespace std;

class Interface {
public:
    // draw all objects
    virtual void draw();

    // update interface
    virtual bool update();

    // start sound
    void start_sound() {al_play_sample_instance(backgroundSound);}
    // stop sound
    void stop_sound() {al_stop_sample_instance(backgroundSound);}

    // load sound and backgroundImage
    Interface(string,string);
    void destroy_Interface();
    ~Interface();

protected:
    ALLEGRO_SAMPLE *sample = nullptr;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = nullptr;

    ALLEGRO_BITMAP * backgroundImage = nullptr;
  
};

#endif // INTERFACCE_H