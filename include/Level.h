#ifndef LEVEL_H
#define LEVEL_H

#include "global.h"
#include "Snake.h"
#include "Stone.h"
#include "Interface.h"
#include <vector>

using namespace std;

class Level: public Interface {
public:
    void draw() override;

    // update all object
    bool update() override;

    // process trigered by key
    GAME_STATE key_triger(int key);

    // load level
    bool load_level(int);

    // reset
    void level_reset(int);

    // print level map
    void print_map();

    //level id
    int getID() {return level_idx;}

    //set key lock
    void set_key_lock() {key_lock = true;key_lock_count=0;}

    //update key lock
    void update_key_lock() {
        if(key_lock && (++key_lock_count%key_lock_num == 0)) {
            key_lock = false;
            key_lock_count = 0;
        }
    }

    // constructor and deletor
    Level(int);
    void destroy_level();
    ~Level();

private:
    static inline DIRCTION KEY_TO_DIRC(int);

    inline OBJ_TYPE& is(Pos pos) {return map.at(pos.first).at(pos.second);}
    bool CanMove(Pos,DIRCTION);

    int level_idx;
    Map map;
    Snake *snake;
    std::vector<Object*> object;

    ALLEGRO_BITMAP *  Ground_image;
    ALLEGRO_BITMAP *  Stone_image;
    ALLEGRO_BITMAP *  Apple_image;
    ALLEGRO_BITMAP *  Snake_head_image;
    ALLEGRO_BITMAP *  Snake_body_image;
    ALLEGRO_BITMAP *  End_point_image;

    bool key_lock = false;
    int key_lock_count = 0;
    const int key_lock_num = KEY_LOCK_NUM;
};

#endif // LEVEL_H