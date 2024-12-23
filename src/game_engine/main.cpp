#include <iostream>
#include <string>

#include "SDL2/SDL.h"

#include "engine/engine.hpp"

#ifndef PROJECT_NAME
    #define PROJECT_NAME ""
#endif

int main(const int argc, const char* argv[]) {

    engine::Engine::getInstance()->init();

    constexpr int FPS = 60;
    constexpr int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (true) {
        frameStart = SDL_GetTicks64();

        engine::Engine::getInstance()->events();
        engine::Engine::getInstance()->update();
        engine::Engine::getInstance()->render();

        frameTime = SDL_GetTicks64() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;
}