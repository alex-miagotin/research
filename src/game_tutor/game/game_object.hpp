#pragma once

class SDL_Texture;
struct SDL_Rect;

class GameObject {
public:

    GameObject(const char* texturesheet, int x, int y);
    ~GameObject() {}

    void update();
    void render();

private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};