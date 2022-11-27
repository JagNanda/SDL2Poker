
#include "Game.h"
#include <iostream>

int main(int argc, char* args[])
{

    Game* game = Game::Instance();
    if (game->Init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN) != true) {
        return -1;
    }

    while (game->IsRunning()) {

        game->HandleEvents();
        game->Update();
        game->Render();

    }

    game->Clean();


    return 0;
}

