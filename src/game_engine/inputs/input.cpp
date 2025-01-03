#include "input.hpp"
#include "../core/engine.hpp"

Input* Input::m_instance = nullptr;

Input::Input(/* args */)
{
    m_keyboardState = SDL_GetKeyboardState(nullptr);
}

Input::~Input()
{
}

void Input::listen()
{
    SDL_Event m_event;
    while(SDL_PollEvent(&m_event)) {
        switch (m_event.type)
        {
        case SDL_QUIT:
            core::Engine::getInstance()->quit();
            break;

        case SDL_KEYDOWN:
            keyDown();
            break;

        case SDL_KEYUP:
            keyUp();
            break;

        default:
            break;
        }
    }
}

bool Input::getKeyDown(SDL_Scancode key)
{
    return m_keyboardState[key] == 1;
}

void Input::keyDown()
{
    m_keyboardState = SDL_GetKeyboardState(nullptr);
}

void Input::keyUp()
{
    m_keyboardState = SDL_GetKeyboardState(nullptr);
}