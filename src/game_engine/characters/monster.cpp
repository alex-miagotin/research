#include "monster.hpp"

#include <SDL2/SDL.h>

#include "../graphics/texture_manager.hpp"
#include "../inputs/input.hpp"

#include "../camera/camera.hpp"

Monster::Monster(const Properties& properties): GameObject(properties) {
    m_rigidbody = new core::physics::Rigidbody();

    m_animation = new Animation();
    m_animation->setProperties(m_textureID, 5, 4, 100, properties.spriteFlip);
};

void Monster::update(float dt) {
    m_animation->setProperties(m_textureID, 5, 4, 100);
    m_rigidbody->unsetForce();

    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_A)) {
        m_rigidbody->applyForceX(5.0f * UPWARD);
        m_animation->setProperties(m_textureID, 8, 6, 100, SDL_FLIP_HORIZONTAL);
    }

    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_D)) {
        m_rigidbody->applyForceX(5.0f * DOWNWARD);
        m_animation->setProperties(m_textureID, 8, 6, 100);
    }

    m_rigidbody->update(dt);

    m_transform->translateX(m_rigidbody->getPosition().x);
    m_transform->translateY(m_rigidbody->getPosition().y);

    m_animation->update();
}
    
void Monster::render() {
    m_animation->render(m_transform->getPosition()->x, m_transform->getPosition()->y, m_width, m_height);

    auto cam = game_engine::Camera::getInstance()->getPosition();
    SDL_Rect rect = {m_transform->getPosition()->x - cam.x, m_transform->getPosition()->y - cam.y, m_width, m_height};
    SDL_RenderDrawRect(core::Engine::getInstance()->getRenderer(), &rect);
}
    
void Monster::clean() {
    graphics::TextureManager::getInstance()->drop(m_textureID);
}