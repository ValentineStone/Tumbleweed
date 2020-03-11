#pragma once
#include "tumbleweed.h"


class Player: public Entity {
    public:
    int x;
    int y;
    int vel = 1;
    int r = 5;
    bool moving_down  = false;
    bool moving_up    = false;
    bool moving_right = false;
    bool moving_left  = false;
    SkPaint paint;

    Player(int _x, int _y): x(_x), y(_y) {
        paint.setColor(SK_ColorWHITE);
        paint.setStyle(SkPaint::kStroke_Style);
    }
    void render(SkCanvas* _c) {
        _c->drawCircle(x, y, r, paint);
    }
    void update(State* _s) {
        int dx = 0;
        int dy = 0;
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