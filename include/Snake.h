#ifndef SNAKE_H
#define SNAKE_H

#include "global.h"
#include "Object.h"
#include "Body.h"
#include <vector>

class Snake {
public:
    void draw();
    bool update();

    Snake(std::vector<Pos>&,ALLEGRO_BITMAP *,ALLEGRO_BITMAP *);

    bool isFall = false;
    MOVE_DIRCTION move_direction = NONE;
    MOVE_DIRCTION heading = NONE;

    float head_x=0;
    float head_y=0;

    std::vector<Body*> body;

};

#endif // SNAKE_H