#include <iostream>
#include <string>

#include "SDL2/SDL.h"

#include "game/game.hpp"

#ifndef PROJECT_NAME
    #define PROJECT_NAME ""
#endif

int main() {
    constexpr int FPS = 60;
    constexpr int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    Game *game = new Game();
    game->init({PROJECT_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 32 * 25, 32 * 20, false, 2, 32});

    while (game->running()) {
        frameStart = SDL_GetTicks64();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks64() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}