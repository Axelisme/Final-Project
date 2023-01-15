#ifndef BODY_H
#define BODY_H

#include "global.h"
#include "Object.h"
#include <vector>

class Body: public Object {
public:
    void draw();

    OBJ_TYPE type = BODY;
    bool isFall = false;
    BODY_DIRCTION dirc;

    Body(Pos,OBJ_TYPE);
    
};

#endif // BODY_H