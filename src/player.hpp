#pragma once
#include "tumbleweed.h"

namespace game {

class player_t: public tw::entity_t {
    public:
    int x;
    int y;
    int vel = 1;
    int r = 5;
    bool moving_down  = false;
    bool moving_up    = false;
    bool moving_right = false;
    bool moving_left  = false;
    tw::paint_t paint;

    player_t(int _x, int _y): x(_x), y(_y) {
        paint.setColor(tw_color(WHITE));
        paint.setStyle(SkPaint::kStroke_Style);
    }
    void render(tw::canvas_t* _c) {
        _c->drawCircle(x, y, r, paint);
    }
    void update(tw::state_t* _s) {
        int dx = 0;
        int dy = 0;
        if (moving_up)    dy -= vel;
        if (moving_left)  dx -= vel;
        if (moving_down)  dy += vel;
        if (moving_right) dx += vel;
        x += dx;
        y += dy;
    }
    void handle_event(tw::event_t* _e) {
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

}