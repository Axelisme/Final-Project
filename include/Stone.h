#ifndef STONE_H
#define STONE_H

#include "global.h"
#include "Object.h"

class Stone: public Object {
public:
    bool update() override;

    Stone(float,float,std::vector<ALLEGRO_BITMAP *>*);

private:
    bool isFall = false;
    
};

#endif // STONE_H