#pragma once

#include <SDL2/SDL.h>

class Animation
{
public:
    Animation() = default;

    void update();
    void render(float x, float y, float spriteWidth, float spriteHeight);
    void setProperties(const char* textureId, const int row, const int frameCount, const int animSpeed, const SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    int m_spriteRow, m_spriteFrame, m_animSpeed, m_frameCount;
    const char* m_textureId;
    SDL_RendererFlip m_flip;

};
