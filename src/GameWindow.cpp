#include "global.h"
#include "GameWindow.h"
#include <iostream>
#include <unistd.h>

using namespace std;

void GameWindow::Set_workdir() {
    char temp[1024];
    int n = readlink("/proc/self/exe", temp, 1024);
    temp[n] = '\0';
    WORKDIR = temp;
    WORKDIR = WORKDIR.substr(0,WORKDIR.find("/bin"));
    show_msg(WORKDIR);
}

void GameWindow::game_load() {
    cout << "Game Initializing...\n";
    /*
        for image and sound
    */

    level = new Level(1);
    menu = new Menu(START);

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
        case ALLEGRO_EVENT_TIMER: {                  // meet time update
            update();
            draw();
            break;
        }
        case ALLEGRO_EVENT_DISPLAY_CLOSE: {          // if close the window
            state = GAME_TERMINATE;
            return;
        }
        case ALLEGRO_EVENT_KEY_DOWN: {               // if pulse a key
            // process for different state
            if(state==GAME_LEVEL)
                    state = level->key_triger(event.keyboard.keycode);
            break;
        }
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {      // if click
            // process for different state
            if(state==GAME_MENU)
                    state = menu->mouse_triger(event.mouse.button);
            break;
        }
    }
}

void GameWindow::update() {
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
    if (! al_init()) raise_err("allegro initial fail");

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

    // load work dir
    Set_workdir();

    // first state is game menu
    state = FIRST_STATE;

    // Create Display
    display = al_create_display(width,height);
    if(display==nullptr) raise_err("can't not create display window");
    al_set_window_position(display,0,0);

    // Create event queue
    event_queue = al_create_event_queue();
    if(event_queue==nullptr) raise_err("can't not create event_queue");

    // Create timer
    timer = al_create_timer(1.0 / FPS);
    if(timer==nullptr) raise_err("can't not create timer");

    // Create sound
    if(!al_reserve_samples(3)) raise_warn("can't not initial sound");

}

void GameWindow::game_reset() {
    level->reset();
    state = FIRST_STATE;
}

void GameWindow::game_destroy() {
    game_reset();

    al_destroy_display(display);            // delete display
    al_destroy_event_queue(event_queue);    // delete event_queue
    al_destroy_timer(timer);                // delete timer

    delete level;
    delete menu;
}

GameWindow::~GameWindow() {
    game_destroy();
}
