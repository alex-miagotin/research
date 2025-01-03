#pragma once

#include "vector2D.hpp"

namespace core::physics {

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

#define UPWARD -1
#define DOWNWARD 1

class Rigidbody
{
public:
    Rigidbody() {
        m_mass = UNI_MASS;
        m_gravity = GRAVITY;
    };
    ~Rigidbody() = default;

    inline void setMass(float mass) { m_mass = mass; }
    inline void setGravity(float gravity) { m_gravity = gravity; }

    inline void applyForce(const Vector2D& force) { m_force = force; }
    inline void applyForceX(const float& fX) { m_force.x = fX; }
    inline void applyForceY(const float& fY) { m_force.y = fY; }
    inline void unsetForce() { m_force.zero(); }

    inline void applyFriction(const Vector2D& friction) { m_friction = friction; }
    inline void applyFrictionX(const float& fX) { m_friction.x = fX; }
    inline void applyFrictionY(const float& fY) { m_friction.y = fY; }
    inline void unsetFriction() { m_friction.zero(); }

    inline Vector2D getPosition() const { return m_position; }
    inline Vector2D getVelocity() const { return m_velocity; }
    inline Vector2D getAcceleration() const { return m_acceleration; }
    inline float getMass() const { return m_mass; }

    void update(float dt)
    {
        m_acceleration.x = (m_force.x + m_friction.x) / m_mass;
        m_acceleration.y = m_gravity + m_force.y / m_mass;

        m_velocity = m_acceleration * dt;
        m_position = m_velocity * dt;
    }

private:
    float m_mass;
    float m_gravity;

    Vector2D m_force;
    Vector2D m_friction;

    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
};

} // namespace core::physics
