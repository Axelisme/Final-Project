#ifndef BUTTON_H
#define BUTTON_H

#include "global.h"
#include "Object.h"
#include <vector>

class Button: public Object {
public:
    Button(Pos,ALLEGRO_BITMAP*,EFFECT,std::vector<Pos>);
};

#endif // BUTTON_H