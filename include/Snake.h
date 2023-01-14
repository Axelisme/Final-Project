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

    void EatApple(Pos);
    Pos Next_Pos();

    Snake(std::vector<Pos>&,ALLEGRO_BITMAP *,ALLEGRO_BITMAP *);

    bool isFall = false;
    bool next_apple = false;
    MOVE_DIRCTION move_direction = NONE;
    MOVE_DIRCTION heading = NONE;

    Pos head = {0.0,0.0};

    std::vector<Body*> body;

};

#endif // SNAKE_H