#ifndef SNAKE_H
#define SNAKE_H

#include "global.h"
#include "Object.h"
#include "Body.h"
#include <deque>

class Snake {
public:
    void draw();
    bool update();

    Pos Next_Pos();

    Snake(std::vector<Pos>&,ALLEGRO_BITMAP *,ALLEGRO_BITMAP *);
    ~Snake();

    bool isFall = false;
    bool can_eat_apple = false;
    DIRCTION move_direction = NONE;
    DIRCTION heading = NONE;

    Pos head = {0.0,0.0};

    std::deque<Body*> body;

private:
    DIRCTION Cal_Dirc(Pos,Pos);
    void Move_all();
    void Move_forward();
    void Move_extend();
    friend bool SnakeCanMove(Snake*,DIRCTION,Map&,Map&);

    // image
    ALLEGRO_BITMAP * Image_head = nullptr;
    ALLEGRO_BITMAP * Image_body = nullptr;
};

#endif // SNAKE_H