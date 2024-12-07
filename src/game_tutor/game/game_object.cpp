#include <SDL2/SDL.h>

#include "texture_manager.hpp"
#include "game_object.hpp"


GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y): renderer(ren), objTexture(TextureManager::LoadTexture(texturesheet, ren))
{
    xpos = x;
    ypos = y;
}

void GameObject::update()
{
    xpos++;
    // ypos++;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;


    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void GameObject::render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}