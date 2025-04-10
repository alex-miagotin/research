#include "texture_manager.hpp"

#include <string>

#include <SDL_image.h>

#include "../core/engine.hpp"
#include "../camera/camera.hpp"

#ifndef ASSETS_PATH
    #define ASSETS_PATH ""
#endif

namespace graphics {

TextureManager* TextureManager::m_instance = nullptr;

bool TextureManager::load(const char* id, const char* fileName)
{
    SDL_Surface* tmpSurface = IMG_Load((std::string(ASSETS_PATH) + fileName).c_str());
    if (tmpSurface == NULL)
    {
        SDL_Log("Unable to load image %s. SDL_image Error: %s\n", fileName, IMG_GetError());
        return false;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(core::Engine::getInstance()->getRenderer(), tmpSurface);
    SDL_FreeSurface(tmpSurface);

    if (tex == nullptr)
    {
        SDL_Log("Unable to create texture from %s. SDL Error: %s\n", fileName, SDL_GetError());
        return false;
    }

    textures[id] = tex;

    return true;
}

void TextureManager::drop(const char* id)
{
    SDL_DestroyTexture(textures[id]);
    textures.erase(id);
}

void TextureManager::clean()
{
    for (auto& texture : textures)
    {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

    IMG_Quit();

    SDL_Log("Texture Manager Cleaned");
}

void TextureManager::render(const char* id, const int x, const int y, const int width, const int height, const int row, const int frame, SDL_RendererFlip flip)
{
    core::physics::Vector2D camera = game_engine::Camera::getInstance()->getPosition();
    SDL_Rect srcRect = {width * frame, height * row, width, height};
    SDL_Rect destRect = {x - camera.x, y - camera.y, width, height};

    SDL_RenderCopyEx(core::Engine::getInstance()->getRenderer(), textures[id], &srcRect, &destRect, 0.0, NULL, flip);
}

void TextureManager::renderBackground(const char* id, const int x, const int y, const int width, const int height, const int row, const int frame, SDL_RendererFlip flip)
{
    core::physics::Vector2D camera = game_engine::Camera::getInstance()->getPosition();
    SDL_Rect srcRect = {width * frame, height * row, width, height};
    SDL_Rect destRect = {x - camera.x * 0.5f, y - camera.y * 0.5f, width, height};

    SDL_RenderCopyEx(core::Engine::getInstance()->getRenderer(), textures[id], &srcRect, &destRect, 0.0, NULL, flip);
}

} // namespace graphics