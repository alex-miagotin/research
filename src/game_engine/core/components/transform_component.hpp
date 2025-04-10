#pragma once

#include "../physics/vector2D.hpp"

namespace core::components {

class TransformComponent {
private:
    using Vector2D = core::physics::Vector2D;

    Vector2D position;

public:
    TransformComponent();
    TransformComponent(const float& x, const float& y);

    ~TransformComponent() = default;

    void translateX(const float& dx);
    void translateY(const float& dy);
    void translate(const Vector2D& vec);

    const Vector2D* getPosition();
    void setPosition(const Vector2D& vec);
};

} // namespace core.components