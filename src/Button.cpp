#include "Button.h"


Button::Button(Pos pos,ALLEGRO_BITMAP* img,EFFECT eff,std::vector<Pos> eff_pos):
        Object(pos,BUTTON,img,OBJECT_IMAGE_SIZE,OBJECT_IMAGE_SIZE) {
    effect = eff;
    Effect_pos = eff_pos;
    triger = false;
}