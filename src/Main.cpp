#include "GameWindow.h"

bool GameWindow::Mute = false;

int main() {
    work_dir_init();
    
    GameWindow* SnakeGame = new GameWindow();

    SnakeGame->game_play();

    delete SnakeGame;
}