#ifndef GANEWINDOW_H
#define GANEWINDOW_H

#include "global.h"
#include "Menu.h"
#include "Level.h"
#include <string>

#define LOCKTIME 30
#define FPS 40

using namespace std;

class GameWindow {
public:
    // Draw function
    void draw();
    // update object
    void update();

    // debug information
    void raise_err(ERR_MSG state,string msg);
    void raise_warn(string msg);
    void show_msg(string msg);

    // game process
    void game_load();
    void game_play();
    void game_reset();
    void game_destroy();

    // Create and destroy
    GameWindow();
    ~GameWindow();

    // work dir path
    static string WORKDIR;
    
private:
    // set work dir path
    void Set_workdir();

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
    GAME_STATE state = GAME_MENU;

    // event
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    ALLEGRO_EVENT event;

    // Time
    ALLEGRO_TIMER *timer = nullptr;

    // bottom lock
    int lockcount = 0;
    bool islock = false;
};


#endif // GANEWINDOW_H
