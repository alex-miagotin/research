#pragma once

#include "../core/physics/vector2D.hpp"
#include "../core/common.hpp"
#include "../core/engine.hpp"

namespace game_engine {

class Camera {
public:
    using Point = core::physics::Vector2D;
    inline static Camera* getInstance() {
        if (instance == nullptr) {
            instance = new Camera();
        }
        return instance;
    }

    inline core::common::Rect getViewBox() const {
        return m_viewBox;
    }

    inline const Point& getPosition() {
        return m_position;
    }

    inline void setTarget(const Point* target) {
        m_target = target;
    }

    void setViewBox(core::common::Rect viewBox);

    void update(float dt);

private:
    Camera() {};
    const Point* m_target;
    Point m_position;

    core::common::Rect m_viewBox{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    static Camera* instance;
};

} // namespace game_engine
