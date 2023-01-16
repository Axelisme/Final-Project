#ifndef BODY_H
#define BODY_H

#include "global.h"
#include "Object.h"
#include <vector>

class Body: public Object {
public:
    void draw() override;
    bool update() override;

    DIRCTION move_dirc = NONE;
    DIRCTION from_dirc;
    DIRCTION to_dirc;

    ALLEGRO_BITMAP *image_head = nullptr;
    ALLEGRO_BITMAP *image_body_straight = nullptr;
    ALLEGRO_BITMAP *image_body_turn = nullptr;

    Body(Pos,OBJ_TYPE,ALLEGRO_BITMAP*,
                      ALLEGRO_BITMAP*,
                      ALLEGRO_BITMAP*,
                      DIRCTION,DIRCTION);
    ~Body();
    
};

#endif // BODY_H