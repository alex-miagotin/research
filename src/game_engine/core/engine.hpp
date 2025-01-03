#pragma once

#include <SDL2/SDL.h>

#include "../map/game_map.hpp"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

namespace core {

class Engine
{
public:
    static Engine* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new Engine();
        }

        return m_instance;
    }

    bool init();
    bool cleanup();
    void quit();

    void update();
    void render();
    void events();

    inline bool isRunning() const { return m_isRunning; }
    SDL_Renderer* getRenderer() const { return m_renderer; }

private:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    bool m_isRunning = false;
    static Engine* m_instance;

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Event m_event;

    map::GameMap* m_levelMap;
};

} // namespace core