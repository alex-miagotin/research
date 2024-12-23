#pragma once

#include <map>

#include "texture_manager.hpp"
#include "common/vector2D.hpp"
#include "ecs/ecs.hpp"

class SDL_Texture;

class AssetManager {
public:
    AssetManager(Manager *);
    ~AssetManager();

    void addTexture(const char* id, const char* path);
    SDL_Texture* getTexture(const char* id);

    // game objects
    void createProjectile(Vector2D pos, Vector2D vel, int range, int speed, const char* id);


private:
    Manager* manager;
    std::map<const char*, SDL_Texture*> textures;
    
    void clean();
};
