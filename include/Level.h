#ifndef LEVEL_H
#define LEVEL_H

#include "global.h"
#include "Snake.h"
#include "Stone.h"
#include "Button.h"
#include "Interface.h"
#include <list>

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

    // constructor and deletor
    Level(int);
    void destroy_level();
    ~Level();
    LEVEL_STAT level_stat = KEEP;
    DIRCTION Gravity = DOWN;

private:
    static inline DIRCTION KEY_TO_DIRC(int);

    inline OBJ_TYPE& is(Pos pos,Map&_map) {return _map.at(pos.first).at(pos.second);}
    bool CanMove(Pos,OBJ_TYPE,DIRCTION);
    void draw_map();

    int level_idx;
    int mapw;
    int maph;
    Map map;
    Map ground_map;
    Map ob_map;
    Map snake_map;
    Snake *snake;
    std::list<Object*> object;

    ALLEGRO_BITMAP *  Fix_Background_image = nullptr;

    ALLEGRO_BITMAP *  Ground_image = nullptr;
    ALLEGRO_BITMAP *  Stone_image = nullptr;
    ALLEGRO_BITMAP *  Apple_image = nullptr;
    ALLEGRO_BITMAP *  Snake_head_image = nullptr;
    ALLEGRO_BITMAP *  Snake_body_straight_image = nullptr;
    ALLEGRO_BITMAP *  Snake_body_turn_image = nullptr;
    ALLEGRO_BITMAP *  Snake_tail_image = nullptr;
    ALLEGRO_BITMAP *  End_point_image = nullptr;
    ALLEGRO_BITMAP *  Buttom_image = nullptr;
    ALLEGRO_BITMAP *  Spike_image = nullptr;
    ALLEGRO_BITMAP *  Spike_down_image = nullptr;
};

#endif // LEVEL_H