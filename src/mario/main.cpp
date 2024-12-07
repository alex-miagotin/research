#include <iostream>
#include <string>

#include "SDL2/SDL.h"

#include "game/game.hpp"

int main() {
    constexpr int FPS = 60;
    constexpr int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    Game *game = new Game();
    game->init({"Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false});

    while (game->running()) {

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}