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

    Snake(std::vector<Pos>&,ALLEGRO_BITMAP *,
                            ALLEGRO_BITMAP *,
                            ALLEGRO_BITMAP *,
                            ALLEGRO_BITMAP *);
    ~Snake();

    bool isFall;
    bool can_eat_apple;
    bool isDied;
    DIRCTION move_direction;
    DIRCTION heading;

    float window_width = CHUNK_W_NUM;
    float window_height = CHUNK_H_NUM;

    Pos head;

    std::deque<Body*> body;

private:
    void Move_all();
    void Move_forward();
    void Move_extend();

    // image
    ALLEGRO_BITMAP * Image_head = nullptr;
    ALLEGRO_BITMAP * Image_body_straight = nullptr;
    ALLEGRO_BITMAP * Image_body_turn = nullptr;
    ALLEGRO_BITMAP * Image_tail = nullptr;
};

#endif // SNAKE_H