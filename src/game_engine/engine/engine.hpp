#pragma once

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

namespace engine {

class Engine
{
public:
    static Engine* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new Engine();
        }

        return m_instance;
    }

    bool init();
    bool cleanup();
    void quit();

    void update();
    void render();
    void events();

    inline bool isRunning() const { return m_isRunning; }

private:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    bool m_isRunning = false;
    static Engine* m_instance;



};

} // namespace engine