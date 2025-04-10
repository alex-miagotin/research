#pragma once

#include <map>

#include <SDL2/SDL.h>

namespace graphics {

class TextureManager {
public:
    static TextureManager* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new TextureManager();
        }

        return m_instance;
    }

    bool load(const char* id, const char* fileName);
    void drop(const char* id);
    void clean();

    void render(const char* id, const int x, const int y, const int width, const int height, const int row, const int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void renderBackground(const char* id, const int x, const int y, const int width, const int height, const int row, const int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    TextureManager() = default;
    ~TextureManager() = default;

    static TextureManager* m_instance;

    std::map<const char*, SDL_Texture*> textures;
};

} // namespace graphics