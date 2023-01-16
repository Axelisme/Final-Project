#include "Body.h"

void Body::draw() {
    return;
    if(SIMPLY_DISPLAY) {
        al_draw_rectangle((pos.second - width/2 )*CHUNK_WIDTH,
                          (pos.first  - height/2)*CHUNK_HEIGHT,
                          (pos.second + width/2 )*CHUNK_WIDTH,
                          (pos.first  + height/2)*CHUNK_HEIGHT,
                          SIMPLE_COLOR_LIST[type],
                          0);
    } 
    else {
        raise_warn("I don't know how to draw because you don't tell me");
    }
}

bool Body::update() {
    Object::update();
    if(move_dirc!=NONE) {
        move_object(DIRC_TO_POS(move_dirc));
        move_dirc = NONE;
    }
    return true;
}

Body::Body(Pos _pos,OBJ_TYPE T,ALLEGRO_BITMAP *img,DIRCTION _from,DIRCTION _to):
      Object(_pos,T,img,1,1)
{
    show_msg("Create body begin");
    move_dirc = NONE;
    from_dirc = _from;
    to_dirc = _to;
    show_msg("Create body done");
}

Body::~Body() {
    show_msg("Delete body begin");
    show_msg("Delete body done");
}