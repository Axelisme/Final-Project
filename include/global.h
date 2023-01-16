#ifndef GLOBAL_H
#define GLOBAL_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>
#include <iostream>
#include <utility>
#include <vector>

#define Debug 1
#define Show 1
#define SIMPLY_DISPLAY 0

#define FIRST_STATE GAME_LEVEL
#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 800

#define CHUNK_W_NUM 14
#define CHUNK_H_NUM 14
#define MAP_WIDTH  40
#define MAP_HEIGHT 25
#define SEE_MAP_WIDTH 30
#define SEE_MAP_HEIGHT 16
#define CHUNK_WIDTH  (double(DISPLAY_WIDTH)/CHUNK_W_NUM)
#define CHUNK_HEIGHT  (double(DISPLAY_HEIGHT)/CHUNK_H_NUM)
#define MIDDLEGROUND_RATIO 0.7

#define FPS 20
#define LEVEL_NUM 1
#define KEY_LOCK_NUM 0
#define ANI_NUM 4
#define ANI_TOTAL_COUNT 50

const std::string MUSIC_PATH("data/music");
const std::string IMAGE_PATH("data/image");
const std::string LEVEL_PATH("data/level");

#define BLACK  al_map_rgb(  0,  0,  0)
#define RED    al_map_rgb(255,  0,  0)
#define GREEN  al_map_rgb(  0,255,  0)
#define BLUE   al_map_rgb(  0,  0,255)
#define YELLOW al_map_rgb(255,255,  0)
#define CMY    al_map_rgb(  0,255,255)
#define PINK   al_map_rgb(255,  0,255)
#define WRITE  al_map_rgb(255,255,255)

enum GAME_STATE {
    GAME_MENU,
    GAME_LEVEL,
    GAME_TERMINATE
};

enum MENU_TYPE {
    START,
    SELECT_LEVEL,
    IN_GAME
};

#define TYPE_NUM 10
enum OBJ_TYPE {
    EDGE = -1,
    AIR,
    GROUND,
    HEAD,
    BODY,
    END,
    APPLE,
    STONE,
    SPIKE,
    BUTTON
};

enum LEVEL_STAT {
    KEEP = 0,
    STOP,
    NEXT,
    RESTART
};

const ALLEGRO_COLOR SIMPLE_COLOR_LIST[] = {BLACK,GREEN,RED,BLUE,PINK,CMY,WRITE,YELLOW};

enum DIRCTION {
    NONE = 0,
    LEFT,
    UP,
    DOWN,
    RIGHT
};

using Pos = std::pair<double, double>;
using Map = std::vector<std::vector<OBJ_TYPE>>;

extern std::string WORKDIR;

void work_dir_init();

void raise_err(const std::string &);

void raise_warn(const std::string &);

void show_msg(const std::string &);

Pos DIRC_TO_POS(DIRCTION);

DIRCTION POS_TO_DIRC(Pos,Pos);

#endif // GLOBAL_H