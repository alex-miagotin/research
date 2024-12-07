#pragma once

class TransformComponent;
class SpriteComponent;
struct SDL_Rect;

class TileComponent : public Component
{
public:

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int s);

    void init() override;
    // void update() override;
    // void render() override;

private:
    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect tileRect;
    int tileID;
    const char *path;

};
