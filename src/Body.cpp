#include "Body.h"

bool Body::update() {
    Object::update();
    if(move_dirc!=NONE) {
        move_object(DIRC_TO_POS(move_dirc));
        move_dirc = NONE;
    }
    return true;
}

Body::Body(Pos _pos,OBJ_TYPE T,ALLEGRO_BITMAP *img,DIRCTION _from,DIRCTION _to):
      Object(_pos,T,img,3,3)
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