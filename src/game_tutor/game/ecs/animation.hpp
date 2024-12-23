#pragma once

struct Animation {
    int index;
    int frames;
    int speed;

    Animation() {}

    /**
     * @brief Construct a new Animation object
     * i: index of the animation
     * f: number of frames
     * s: speed of the animation
     */
    Animation(int i, int f, int s) {
        index = i;
        frames = f;
        speed = s;
    }
};