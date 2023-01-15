#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"
#include <vector>

class Object {
public:
    // type
    OBJ_TYPE type = AIR;
    bool CanFall = false;
    DIRCTION move_dirc = NONE;

    virtual void draw();
    virtual bool update();

    float &getw() {return width;}
    float &geth() {return height;}
    Pos &getPos() {return pos;}
    ALLEGRO_BITMAP * &getImg() {return Image;}

    void move_object(Pos dp) {pos.first+=dp.first;pos.second+=dp.second;}
    Pos ConvertIdx(int idx);

    Object(Pos _pos,OBJ_TYPE T,ALLEGRO_BITMAP *img,float w,float h):
            pos(_pos),
            type(T),
            Image(img),
            width(w),
            height(h)  {}

protected:
    
    // animation
    int ani_total_count = ANI_TOTAL_COUNT;
    int ani_count = 0;         //count form ani_total_count to 0
    int ani_num = ANI_NUM;
    int ani_image_idx = 0;     //the current image

    // center position
    Pos pos;

    // width and height
    float width = 0;
    float height = 0; 

    // image
    ALLEGRO_BITMAP * Image = nullptr;
    
};

#endif // OBJECT_H