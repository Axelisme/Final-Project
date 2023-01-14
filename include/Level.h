#ifndef LEVEL_H
#define LEVEL_H

#include "global.h"
#include "Snake.h"
#include "Interface.h"
#include <vector>

using namespace std;

class Level: public Interface {
public:
    void draw() override;

    // update all object
    bool update();

    // process trigered by key
    GAME_STATE key_triger(int key);

    // load level
    bool load_level(int);

    // reset
    void reset();

    // print level map
    void print_map();

    // constructor and deletor
    Level(int);
    ~Level();

private:
    inline bool is(int,int,OBJ_TYPE);

    int level_idx;
    Map map;
    Snake *snake;
    std::vector<Object*> object;

    ALLEGRO_BITMAP *  Ground_image;
    ALLEGRO_BITMAP *  Stone_image;
    ALLEGRO_BITMAP *  Apple_image;
    ALLEGRO_BITMAP *  Snake_head_image;
    ALLEGRO_BITMAP *  Snake_body_image;

    bool key_lock = false;
    int key_lock_count = 0;
    const int key_lock_num = KEY_LOCK_NUM;
  
};

#endif // LEVEL_H