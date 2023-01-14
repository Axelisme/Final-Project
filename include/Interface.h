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

    // load sound and backgroundImage
    Interface(string,string);
    ~Interface();

protected:
    ALLEGRO_SAMPLE *sample = nullptr;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = nullptr;

    ALLEGRO_BITMAP * backgroundImage = nullptr;
  
};

#endif // INTERFACCE_H