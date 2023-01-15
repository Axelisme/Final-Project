#ifndef BODY_H
#define BODY_H

#include "global.h"
#include "Object.h"
#include <vector>

class Body: public Object {
public:
    void draw() override;
    bool update() override;

    bool isFall = false;
    DIRCTION from_dirc;
    DIRCTION to_dirc;

    Body(Pos,ALLEGRO_BITMAP *,DIRCTION,DIRCTION);
    ~Body();
    
};

#endif // BODY_H