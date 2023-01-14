#ifndef STONE_H
#define STONE_H

#include "global.h"
#include "Object.h"

class Stone: public Object {
public:
    void update() override;

    Stone(float,float,std::vector<ALLEGRO_BITMAP *>*);

    void triger_fall() {isFall=true;}
    void stop_fall() {isFall=false;}

private:
    bool isFall = false;
    
};

#endif // STONE_H