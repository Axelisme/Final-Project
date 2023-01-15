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
    if(isFall) {
        move_object({1,0});
        isFall = false;
    }
    return true;
}

Body::Body(Pos _pos,ALLEGRO_BITMAP *img,DIRCTION _from,DIRCTION _to):
      Object(_pos,img,1,1)
{
    show_msg("Create body begin");
    isFall = false;
    from_dirc = _from;
    to_dirc = _to;
    show_msg("Create body done");
}

Body::~Body() {
    show_msg("Delete body begin");
    show_msg("Delete body done");
}