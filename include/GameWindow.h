#ifndef GANEWINDOW_H
#define GANEWINDOW_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <string>
#include "Menu.h"
#include "Draw.h"
#include "Level.h"
#include "global.h"

#define LOCKTIME 30
#define FPS 40

using namespace std;

enum GAME_STATE {
    GAME_MENU,
    GAME_LEVEL,
    GAME_TERMINATE
};

class GameWindow:Draw
{
public:
    // Draw function
    void draw();
    void update();

    // debug information
    void raise_err(ERR_MSG state,string msg);
    void raise_warn(string msg);
    void show_msg(string msg);

    // game process
    void game_load();
    void game_play();
    void game_destroy();

    // Create and destroy
    GameWindow();
    ~GameWindow();

    // work dir path
    string WORKDIR;
    void Set_workdir();

private:
    // inner process
    void game_begin();
    void game_process();

    // display 
    ALLEGRO_DISPLAY* display = nullptr;
    const int width = 800;
    const int height = 600;

    // menu
    Menu *menu = nullptr;

    // level
    Level *level = nullptr;

    // state
    GAME_STATE state;

    // event
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    ALLEGRO_EVENT event;

    // Time
    ALLEGRO_TIMER *timer = nullptr;

    // redraw
    bool redraw = false;

    // bottom lock
    int lockcount = 0;
    bool islock = false;
};


#endif // GANEWINDOW_H
