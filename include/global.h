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

#define Debug 1

#define FIRST_STATE GAME_MENU
#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600
#define CHUNK_W_NUM 20
#define CHUNK_H_NUM 10
#define G_VELOCITY 0.5     //CHUNK
#define FPS 40
#define TYPE_NUM 5
#define KEY_LOCK_NUM 1000
#define ANI_TOTAL_COUNT 50

#define CHUNK_WIDRH  (float(DISPLAY_WIDTH)/CHUNK_W_NUM)
#define CHUNK_HEIGHT  (float(DISPLAY_HEIGHT)/CHUNK_H_NUM)

#define BLACK al_map_rgb(0, 0, 0)

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

enum OBJ_TYPE {
    GROUND,
    STONE,
    APPLE,
    HEAD,
    BODY
};

const int ANI_NUM[TYPE_NUM]={4,4,4,4,4};

void raise_err(const std::string &);

void raise_warn(const std::string &);

void show_msg(const std::string &);

#endif // GLOBAL_H