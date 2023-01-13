#include "GameWindow.h"

int main() {
    GameWindow* SnakeGame = new GameWindow();

    SnakeGame->game_play();

    delete SnakeGame;
}