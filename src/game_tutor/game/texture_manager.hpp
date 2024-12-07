#pragma once

class SDL_Texture;
class SDL_Renderer;

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
    static void Render(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};