#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"
#include <vector>

class Object {
public:
    // type
    OBJ_TYPE type = AIR;
    DIRCTION move_dirc = NONE;
    float rotate_angle = 0;

    // image
    ALLEGRO_BITMAP * Image = nullptr;

    // window x and y
    float window_x = 0;
    float window_y = 0; 

    virtual void draw();
    virtual bool update();

    float &getw() {return width;}
    float &geth() {return height;}
    Pos &getPos() {return pos;}
    ALLEGRO_BITMAP * &getImg() {return Image;}

    void move_object(Pos dp) {pos.first+=dp.first;pos.second+=dp.second;}
    Pos ConvertIdx(int idx);

    Object(Pos,OBJ_TYPE,ALLEGRO_BITMAP*,float,float);

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

    // image width and height
    float image_width = 0;
    float image_height = 0;
    
};

#endif // OBJECT_H