#include "ecs.hpp"

void Entity::addGroup(Group mGroup) {
    groupBitSet[mGroup] = true;
    manager.addToGroup(this, mGroup);
}