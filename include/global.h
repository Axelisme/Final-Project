#ifndef GLOBAL_H
#define GLOBAL_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define STR_(X) #X
#define STR(X) STR_(X)

#define Debug 1

enum ERR_MSG {
    INIT_FAIL,
    START_FAIL,
    RUNTIME_FAIL,
    KEY_TERNIMATE
};

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
    Air,
    Ground,
    Stone,
    Apple
};


#endif // GLOBAL_H