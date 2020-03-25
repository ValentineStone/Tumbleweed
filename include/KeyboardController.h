#pragma once
#include "tumbleweed.h"

template <typename T>
class KeyboardController: public Entity {
    public:
    T x = 0;
    T y = 0;
    T dx;
    T dy;
    T vel = 1;
    bool moving_down  = false;
    bool moving_up    = false;
    bool moving_right = false;
    bool moving_left  = false;

    KeyboardController(T _vel): vel(_vel) {}
    
    void update(State* _s) {
        dx = 0;
        dy = 0;
        if (moving_up)    dy -= vel;
        if (moving_left)  dx -= vel;
        if (moving_down)  dy += vel;
        if (moving_right) dx += vel;
        x += dx;
        y += dy;
    }
    void handle_event(SDL_Event* _e) {
        auto key = _e->key.keysym.sym;
        if (_e->type == SDL_KEYDOWN) {
            if      (key == SDLK_w) moving_up    = true;
            else if (key == SDLK_a) moving_left  = true;
            else if (key == SDLK_s) moving_down  = true;
            else if (key == SDLK_d) moving_right = true;
        }
        else if (_e->type == SDL_KEYUP) {
            if      (key == SDLK_w) moving_up    = false;
            else if (key == SDLK_a) moving_left  = false;
            else if (key == SDLK_s) moving_down  = false;
            else if (key == SDLK_d) moving_right = false;
        }
    }
};