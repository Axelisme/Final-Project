#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"
#include <vector>

class Object {
public:
    // type
    OBJ_TYPE type;
    DIRCTION move_dirc = NONE;

    void draw();
    virtual bool update();

    float &getw() {return width;}
    float &geth() {return height;}
    Pos &getPos() {return pos;}
    ALLEGRO_BITMAP * &getImg() {return Image;}

    void move_object(Pos);
    Pos ConvertIdx(int idx);

protected:
    
    // animation
    int ani_total_count;
    int ani_count;         //count form ani_total_count to 0
    int ani_num;
    int ani_image_idx;     //the current image

    // center position
    Pos pos;

    // width and height
    float width = 0;
    float height = 0; 

    // image
    ALLEGRO_BITMAP * Image = nullptr;
    
};

#endif // OBJECT_H