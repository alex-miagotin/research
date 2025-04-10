#pragma once

constexpr float TARGET_FPS = 60.0f;
constexpr float TARGET_DELTA_TIME = 1.5f;

class Timer
{

public:
    static Timer* getInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new Timer();
        }
        return m_instance;
    }

    void tick();
    inline float getDeltaTime() const { return m_deltaTime; }
    inline float getInitialisedTime() const;

private:
    Timer() = default;
    ~Timer() = default;

    static Timer *m_instance;
    float m_deltaTime;
    float m_lastTime;

};
