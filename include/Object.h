#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"
#include <vector>

class Object {
public:
    // type
    OBJ_TYPE type;
    MOVE_DIRCTION move_dirc = NONE;

    void draw();
    virtual bool update();

    float getx() {return x;}
    float gety() {return y;}
    float getw() {return width;}
    float geth() {return height;}

    void move(float _x,float _y) {x+=_x;y+=_y;}
    void setxy(float _x,float _y) {x=_x;y=_y;}

protected:
    
    // animation
    int ani_total_count;
    int ani_count;         //count form ani_total_count to 0
    int ani_num;
    int ani_image_idx;     //the current image

    // center position
    float x = 0;
    float y = 0;

    // width and height
    float width = 0;
    float height = 0; 

    // image
    std::vector<ALLEGRO_BITMAP *>* Image = nullptr;
    
};

#endif // OBJECT_H