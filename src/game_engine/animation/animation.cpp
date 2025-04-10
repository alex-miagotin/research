#include "animation.hpp"

#include "../graphics/texture_manager.hpp"

void Animation::update()
{
    m_spriteFrame = (SDL_GetTicks64() / m_animSpeed) % m_frameCount;
}

void Animation::render(float x, float y, float spriteWidth, float spriteHeight)
{
    graphics::TextureManager::getInstance()->render(m_textureId, x, y, spriteWidth, spriteHeight, m_spriteRow, m_spriteFrame, m_flip);
}

void Animation::setProperties(const char* textureId, const int row, const int frameCount, const int animSpeed, const SDL_RendererFlip flip)
{
    m_textureId = textureId;
    m_spriteRow = row;
    m_frameCount = frameCount;
    m_animSpeed = animSpeed;
    m_flip = flip;
}