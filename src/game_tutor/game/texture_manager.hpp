#pragma once

class SDL_Texture;
class SDL_Renderer;

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Render(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};