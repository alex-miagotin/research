#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "common/common.hpp"

#include "assets_manager.hpp"

class Game {

public:
    Game();
    ~Game();

    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayers,
        groupEnemies,
        groupColliders,
        groupProjectiles,
    };

    struct Configuration {
        const char* title;
        int xpos;
        int ypos;
        int width;
        int height;
        bool fullscreen;
        int scale;
        int tileSize;
    };

    void init(const Configuration& config);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; } 
    
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static Rect camera;
    static AssetManager* assets;
private:
    SDL_Window *window;
    int count = 0;
    Configuration config;
};