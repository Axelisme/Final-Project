#ifndef LEVEL_H
#define LEVEL_H

#include "global.h"
#include "Map.h"
#include "Snake.h"
#include "Interface.h"

using namespace std;

class Level: public Interface {
public:
    //draw
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
    Map *map;
    Snake *snake;
  
};

#endif // LEVEL_H