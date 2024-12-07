#pragma once

class SDL_Renderer;
class SDL_Texture;
struct SDL_Rect;

class Map {
public:

    Map(SDL_Renderer* ren);
    ~Map() {
        SDL_DestroyTexture(dirt);
        SDL_DestroyTexture(grass);
        SDL_DestroyTexture(water);
    }

    void loadMap(int arr[20][25]);
    void render();
private:
    SDL_Renderer* renderer;

    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;
    SDL_Rect srcRect, destRect;

    int map[20][25];
};