#include "camera.hpp"

namespace game_engine {

Camera* Camera::instance = nullptr;

void Camera::setViewBox(core::common::Rect viewBox) {
    m_viewBox = viewBox;
}

void Camera::update(float dt) {
    if (m_target == nullptr) {
        return;
    }

    m_viewBox.x = m_target->x - SCREEN_WIDTH / 2;
    m_viewBox.y = m_target->y - SCREEN_HEIGHT / 2;

    if (m_viewBox.x < 0) {
        m_viewBox.x = 0;
    }

    if (m_viewBox.y < 0) {
        m_viewBox.y = 0;
    }

    if (m_viewBox.x > (2*SCREEN_WIDTH - m_viewBox.w)) {
        m_viewBox.x = 2*SCREEN_WIDTH - m_viewBox.w;
    }

    if (m_viewBox.y > (2*SCREEN_HEIGHT - m_viewBox.h)) {
        m_viewBox.y = 2*SCREEN_HEIGHT - m_viewBox.h;
    }

    m_position.x = m_viewBox.x;
    m_position.y = m_viewBox.y;
}

} // namespace game_engine