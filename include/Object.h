#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"
#include <vector>

class Object {
public:
    void draw();
    void update();

    float getx() {return x;}
    float gety() {return y;}
    float getw() {return width;}
    float geth() {return height;}

    void move(float _x,float _y) {x+=_x;y+=_y;}

    Object();
    ~Object();
protected:
    // type
    OBJ_TYPE type;

    // animation
    const int ani_total_count;
    int ani_count;         //count form ani_total_count to 0
    int ani_type_num;      //how many different image for animation
    int ani_image_idx;     //the current image

    // center position
    float x;
    float y;

    // width and height
    float width;
    float height; 

    // image
    std::vector<ALLEGRO_BITMAP *> Image;
    
};

#endif // OBJECT_H