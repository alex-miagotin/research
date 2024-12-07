#pragma once

#include <vector>

class SDL_Window;
class SDL_Renderer;
class ColliderComponent;

class Game {

public:
    Game();
    ~Game();

    struct Configuration {
        const char* title;
        int xpos;
        int ypos;
        int width;
        int height;
        bool fullscreen;
    };

    void init(const Configuration& config);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }

    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;
private:
    bool isRunning{false};
    SDL_Window *window;
    SDL_Renderer *renderer;
    int count = 0;
    Configuration config;
};