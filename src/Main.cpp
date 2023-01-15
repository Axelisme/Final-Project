#include "GameWindow.h"

int main() {
    work_dir_init();
    
    GameWindow* SnakeGame = new GameWindow();

    SnakeGame->game_play();

    delete SnakeGame;
}