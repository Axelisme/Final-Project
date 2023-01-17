#include "GameWindow.h"
#include <iostream>
#include <unistd.h>
#include <sched.h>

using namespace std;

void GameWindow::game_load() {
    show_msg("Game Loading...");

    // create level
    show_msg("Create level");
    level = new Level(FIRST_LEVEL);

    // create menu
    show_msg("Create menu");
    menu = new Menu(state);

    show_msg("Game Load finish");
}

void GameWindow::game_play() {
    // load data
    game_load();

    // start game
    game_begin();

    // process event until terminate
    show_msg("Start to process event");
    double t_now=0.0;
    double t_pre=0.0;
    while(state != GAME_TERMINATE) {
        if(!al_is_event_queue_empty(event_queue))
            game_process();
        else {
            t_now=al_get_time();
            if(t_now-t_pre>=10/FPS) {
                t_pre = t_now;
            }
            else sleep(0);
        }
    }

}

void GameWindow::game_begin() {
    show_msg("Game begining");

    // set timer start
    show_msg("set timer start");
    al_start_timer(timer);

    show_msg("Game begin finish");
}

void GameWindow::game_process() {
    // acquire event
    al_wait_for_event(event_queue, &event);

    // process for different event
    switch(event.type) {
        case ALLEGRO_EVENT_TIMER: {                  // meet time update
            if(!update()) return;
            draw();
            break;
        }
        case ALLEGRO_EVENT_DISPLAY_CLOSE: {          // if close the window
            show_msg("Detect display close, game terminate");
            state = GAME_TERMINATE;
            return;
        }
        case ALLEGRO_EVENT_KEY_DOWN: {               // if pulse a key
            show_msg("Detect key down");
            // process for different state
            if(state==GAME_LEVEL)
                    state = level->key_triger(event.keyboard.keycode);
            break;
        }
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {      // if click
            show_msg("Detect click down");
            // process for different state
            if(state==GAME_MENU)
                    state = menu->mouse_triger(event.mouse.button);
            break;
        }
    }
}

bool GameWindow::update() {
    // menu or level update
    switch(state) {
        case GAME_MENU: {
            state = GAME_LEVEL;
            menu->update();
            return true;
        }
        case GAME_LEVEL: {
            switch(level->level_stat)
            {
                case KEEP:{
                    level->update();
                    break;
                }
                case STOP: {
                    state = GAME_MENU;
                    break;
                }
                case NEXT:{
                    int level_idx = level->getID();
                    if(level_idx == LEVEL_NUM) {
                        state = GAME_TERMINATE;
                        return false;
                    }
                    else{
                        delete level;
                        level = new Level(level_idx+1);
                        return true;
                    }
                }
                case RESTART:{
                    int level_idx = level->getID();
                    delete level;
                    level = new Level(level_idx);
                    return true;
                }
            }
            return true;
        }
        case GAME_TERMINATE: return false;
        default : {
            raise_err("unknown game state");
            state = GAME_TERMINATE;
            return false;
        }
    }
}

void GameWindow::draw() {
    switch(state) {
        case GAME_MENU: {
            menu->draw();
            break;
        }
        case GAME_LEVEL: {
            level->draw();
            break;
        }
        case GAME_TERMINATE: return;
    }
    al_flip_display();
}

GameWindow::GameWindow() {
    // Initial Allegro
    show_msg("Initial Allegor");
    if (! al_init()) raise_err("allegro initial fail");

    // Initial Allegro addon
    show_msg("Initial Allegro addon");
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    // install device
    show_msg("Install device");
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    // first state is game menu
    state = FIRST_STATE;

    // Create Display
    show_msg("Create Display");
    display = al_create_display(width,height);
    if(display==nullptr) raise_err("can't not create display window");
    al_set_window_position(display,0,0);

    // Create event queue
    show_msg("Create even queue");
    event_queue = al_create_event_queue();
    if(event_queue==nullptr) raise_err("can't not create event_queue");

    // Create timer
    show_msg("Create timer");
    timer = al_create_timer(1.0 / FPS);
    if(timer==nullptr) raise_err("can't not create timer");

    // Create sound
    show_msg("Create sound");
    if(!al_reserve_samples(3)) raise_warn("can't not initial sound");

    // register event source
    show_msg("register event source");
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

void GameWindow::game_reset() {
    show_msg("Game reset begin");

    level->level_reset(FIRST_LEVEL);
    state = FIRST_STATE;

    show_msg("Game reset down");
}

void GameWindow::game_destroy() {
    show_msg("Game destroy begin");

    al_destroy_display(display);            // delete display
    al_destroy_event_queue(event_queue);    // delete event_queue
    al_destroy_timer(timer);                // delete timer

    delete level;
    delete menu;

    show_msg("Game destroy done");
}

GameWindow::~GameWindow() {
    show_msg("Game delete begin");

    game_destroy();

    show_msg("Game delete done");
}
