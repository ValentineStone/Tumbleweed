#pragma once
#include "tumbleweed.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
const float PI_F = 3.14159265358979f;

namespace game {

class dotfield_t: public tw::entity_t {
    struct dot_t {
        float x,y,dx,dy;
        dot_t(){
            x = PI_F * std::rand() / (float)RAND_MAX;
            y = PI_F * std::rand() / (float)RAND_MAX * 2;
            dx = .02f * std::rand() / (float)RAND_MAX - .01f;
            dy = .02f * std::rand() / (float)RAND_MAX - .01f;
        }
    };
    std::vector<dot_t> dots;
    tw::paint_t paint;
    tw::paint_t paint_line;
    int width;
    int height;
    int n;

    public:
    dotfield_t(int _width, int _height, int _n):
        width(_width),
        height(_height),
        n(_n)
    {
        init();
        paint.setColor(tw_color(WHITE));
        std::srand(std::time(nullptr));
        for (int i = 0; i < n; i++)
            dots.push_back(dot_t());
    }
    ~dotfield_t() {
        free();
    }

    private:
    void render(tw::canvas_t* _c) {
        for (auto dot : dots) {
            float _x = std::sin(dot.x) * std::cos(dot.y);
            float _y = std::sin(dot.x) * std::sin(dot.y);
            float _z = std::cos(dot.x);

            int x = (_x + 1) / 2 * width;
            int y = (_y + 1) / 2 * height;
            int z = (_z + 1) / 2 * 255;
            paint.setColor(0xff000055 | z | z << 8 | z << 16);
            _c->drawPoint(x, y, paint);
        }
    }
    void update(tw::state_t* _s) {
        for (dot_t& dot : dots) {
            dot.x += dot.dx;
            dot.y += dot.dy;
        }
    }
    void handle_event(tw::event_t* _e) {
    }

    void init() {
    }
    void free() {
    }
};

}