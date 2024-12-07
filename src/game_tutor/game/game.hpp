#pragma once

#include <vector>

class SDL_Window;
class SDL_Renderer;
class ColliderComponent;
union SDL_Event;

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

    static void addTile(int id, int x, int y);
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;
private:
    bool isRunning{false};
    SDL_Window *window;
    int count = 0;
    Configuration config;
};