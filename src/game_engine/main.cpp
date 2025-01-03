#include "SDL2/SDL.h"

#include "core/engine.hpp"
#include "timer/timer.hpp"

#ifndef PROJECT_NAME
    #define PROJECT_NAME ""
#endif

int main(const int argc, const char* argv[]) {

    auto _engine = core::Engine::getInstance();
    _engine->init();

    while (_engine->isRunning()) {
        _engine->events();
        _engine->update();
        _engine->render();

        Timer::getInstance()->tick();        
    }

    _engine->cleanup();

    return 0;
}