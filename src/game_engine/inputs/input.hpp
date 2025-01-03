#pragma once

#include <SDL2/SDL.h>

class Input
{
public:
    static Input* getInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new Input();
        }
        return m_instance;
    }

    void listen();
    bool getKeyDown(SDL_Scancode key);

    // void update();

    // bool isKeyDown();
    // bool isKeyUp();
    // bool isKeyPressed();
    // bool isKeyReleased();

    // bool isMouseButtonDown();
    // bool isMouseButtonUp();
    // bool isMouseButtonPressed();
    // bool isMouseButtonReleased();

    // bool isMouseMotion();

    // bool isMouseWheel();

    // bool isQuit();

    // void clean();

private:
    Input(/* args */);
    ~Input();

    void keyDown();
    void keyUp();

    const Uint8* m_keyboardState;
    static Input* m_instance;
};
