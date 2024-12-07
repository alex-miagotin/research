#include <string>
#include <SDL_image.h>

#include "texture_manager.hpp"


#ifndef RESOURCE_PATH
    #define RESOURCE_PATH ""
#endif

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* ren)
{
    std::string imagePath = std::string(RESOURCE_PATH) + fileName;
    SDL_Surface* tmpSurface = IMG_Load(imagePath.c_str());
    if (tmpSurface == NULL)
    {
        printf("Unable to load image. SDL_image Error: %s\n", IMG_GetError());
        throw "Unable to load image";
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tex;
}

void TextureManager::Render(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(ren, tex, &src, &dest);
}