#ifndef BODY_H
#define BODY_H

#include "global.h"
#include "Object.h"
#include <vector>

class Body: public Object {
public:
    void draw();

    bool isFall = false;
    DIRCTION from_dirc;
    DIRCTION to_dirc;

    void head_to_body(ALLEGRO_BITMAP *);

    Body(Pos,ALLEGRO_BITMAP *,DIRCTION,DIRCTION);
    
};

#endif // BODY_H