#pragma once

#include <SDL2/SDL.h>

#include "../engine/engine.hpp"

namespace sdl_renderer {

class SDLRenderer {
public:
    static SDLRenderer* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new SDLRenderer();
        }

        return m_instance;
    }

    bool init();
    bool cleanup();
    void quit();

    void update();
    void render();
    void events();

    bool isRunning() const { return m_isRunning; }

private:
    SDLRenderer() = default;
    ~SDLRenderer() = default;
    SDLRenderer(const SDLRenderer&) = delete;
    SDLRenderer& operator=(const SDLRenderer&) = delete;

    bool m_isRunning = false;
    static SDLRenderer* m_instance;
};

} // namespace sdl_renderer
