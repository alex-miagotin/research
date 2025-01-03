#pragma once

#include "../game_object/game_object.hpp"
#include "../animation/animation.hpp"
#include "../core/physics/rigid_body.hpp"

class Monster: public GameObject
{
public:
    Monster(const Properties& properties);

    void update(float dt) override final;
    void render() override final;
    void clean() override final;

private:
    const char* m_name = "Monster";

    Animation* m_animation;
    core::physics::Rigidbody* m_rigidbody;
    
};