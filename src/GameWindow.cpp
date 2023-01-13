#include "GameWindow.h"
#include "global.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <filesystem>

using namespace std;

void GameWindow::raise_err(ERR_MSG state,string msg = ""){
    if (Debug) cerr << "error: " << msg << endl;
    game_destroy();
    exit(state);
}

void GameWindow::raise_warn(string msg = ""){
    if (Debug) cerr << "warning: " << msg << endl;
}

void GameWindow::show_msg(string msg = ""){
    cout << "Messenger: " << msg << endl;
}

void GameWindow::Set_workdir() {
    char temp[200];
    readlink("/proc/self/exe", temp, 200);
    WORKDIR = temp;
    WORKDIR = WORKDIR.substr(0,WORKDIR.find("/bin"));
    show_msg(WORKDIR);
}

void GameWindow::game_load() {
    cout << "Game Initializing...\n";

    level = new Level(1);
    menu = new Menu();

}

void GameWindow::game_play() {
    // load data
    game_load();

    // start game
    game_begin();

    // process event until terminate
    while(state != GAME_TERMINATE) {
        if(!al_is_event_queue_empty(event_queue))
            game_process();
    }

    // free the game
    game_destroy();
}

void GameWindow::game_begin() {
    al_start_timer(timer);
}

void GameWindow::game_process() {
    // acquire event
    al_wait_for_event(event_queue, &event);

    // process for different event
    switch(event.type) {
        case ALLEGRO_EVENT_TIMER: {         // meet time update
            redraw = true;
            update();
            draw();
            break;
        }
        case ALLEGRO_EVENT_DISPLAY_CLOSE: { // if close the window
            state = GAME_TERMINATE;
            return;
        }
        case ALLEGRO_EVENT_KEY_DOWN: {      // if pulse a key
            // check whether in lock state
            if(islock) break;

            // process for different state
            switch(state) {
                case GAME_MENU: {
                    
                }
                case GAME_LEVEL: {
                }
                case GAME_TERMINATE: return;
            }

            // set buttom lock
            islock = true;
            lockcount = LOCKTIME;

            break;
        }
    }
}

void GameWindow::update() {
    // buttom lock update
    if(lockcount>0) --lockcount;
    else islock = false;

    // menu or level update
    switch(state) {
        case GAME_MENU: {
            menu->update();
            return;
        }
        case GAME_LEVEL: {
            level->update();
            return;
        }
        case GAME_TERMINATE: return;
    }
}

void GameWindow::draw() {
    switch(state) {
        case GAME_MENU: {
            menu->draw();
            return;
        }
        case GAME_LEVEL: {
            level->draw();
            return;
        }
        case GAME_TERMINATE: return;
    }
}

GameWindow::GameWindow() {
    // Initial Allegro
    if (! al_init()) raise_err(INIT_FAIL,"allegro initial fail");

    // load work dir
    Set_workdir();

    // Create Display
    display = al_create_display(width,height);
    if(display==nullptr) raise_err(INIT_FAIL,"can't not create display window");
    al_set_window_position(display,0,0);

    // Create event queue
    event_queue = al_create_event_queue();
    if(event_queue==nullptr) raise_err(INIT_FAIL,"can't not create event_queue");

    // Create timer
    timer = al_create_timer(1.0 / FPS);
    if(timer==nullptr) raise_err(INIT_FAIL,"can't not create timer");

    // Initial Allegro addon
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    // install device
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    // register event source
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

}

void GameWindow::game_destroy() {
    //delete display
    al_destroy_display(display);

}

GameWindow::~GameWindow() {
    game_destroy();
}
