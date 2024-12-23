#include "assets_manager.hpp"

#include "ecs/transform_component.hpp"
#include "ecs/sprite_component.hpp"
#include "ecs/projectile_component.hpp"
#include "ecs/collider_component.hpp"

#include "game.hpp"

AssetManager::AssetManager(Manager *_manager): manager(_manager)
{

}

AssetManager::~AssetManager()
{
    clean();
    printf("AssetManager destroyed\n");
}

void AssetManager::addTexture(const char* id, const char* path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::getTexture(const char* id)
{
    return textures[id];
}

void AssetManager::createProjectile(Vector2D pos, Vector2D vel, int range, int speed, const char* id)
{
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos, 32, 32, 1);
    projectile.addComponent<SpriteComponent>(id);
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addGroup(Game::groupLabels::groupProjectiles);
}

void AssetManager::clean()
{
    for(auto& tex : textures)
    {
        SDL_DestroyTexture(tex.second);
    }
}
