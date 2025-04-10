#pragma once

#include <SDL2/SDL.h>

#include "../core/interface/IObject.hpp"
#include "../core/components/transform_component.hpp"
#include "../core/common.hpp"

struct Properties
{
    float x;
    float y;
    int width;
    int height;
    const char* textureID;
    SDL_RendererFlip spriteFlip;
};

class GameObject: public core::interface::IObject
{
public:
    GameObject(const Properties& properties) {
        m_transform = new core::components::TransformComponent(properties.x, properties.y);
        m_width = properties.width;
        m_height = properties.height;
        m_textureID = properties.textureID;
        m_flip = properties.spriteFlip;
    };

    inline core::components::TransformComponent* getTransform() const {
        return m_transform;
    }

    inline const int getWidth() const {
        return m_width;
    }

    inline const int getHeight() const {
        return m_height;
    }

protected:
    core::components::TransformComponent* m_transform;
    int m_width;
    int m_height;
    const char* m_textureID;
    SDL_RendererFlip m_flip;
private:
};
