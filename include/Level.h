#ifndef LEVEL_H
#define LEVEL_H

#include "global.h"
#include "Snake.h"
#include "Interface.h"
#include <vector>

using namespace std;

class Level {
public:
    // draw
    void draw();

    // update all object
    void update();

    // process trigered by key
    GAME_STATE key_triger(int key);

    // load level
    bool load_level(int);

    // reset
    void reset();

    // constructor and deletor
    Level(int);
    ~Level();

private:
    int level_idx;
    std::vector<std::vector<OBJ_TYPE>> map;
    Snake *snake;

    std::vector<ALLEGRO_BITMAP *>  Ground_image;
    std::vector<ALLEGRO_BITMAP *>  Stone_image;
    std::vector<ALLEGRO_BITMAP *>  Apple_image;
    std::vector<ALLEGRO_BITMAP *>  Snake_head_image;
    std::vector<ALLEGRO_BITMAP *>  Snake_body_image;

    bool key_lock = false;
    int key_lock_count = 0;
    const int key_lock_num = KEY_LOCK_NUM;
  
};

#endif // LEVEL_H