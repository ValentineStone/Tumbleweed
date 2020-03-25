#pragma once
#include "tumbleweed.h"
#include "KeyboardController.h"

const float PI_F = 3.14159265358979f;

class Dotfield: public Entity {
    struct __Dot {
        float x,y,dx,dy;
        int variant = 0;
        __Dot(float _x, float _y, float _dx, float _dy):
            x(_x), y(_y), dx(_dx), dy(_dy) {}
        __Dot() {
            x = PI_F * std::rand() / (float)RAND_MAX;
            y = PI_F * std::rand() / (float)RAND_MAX * 2;
            dx = .02f * std::rand() / (float)RAND_MAX - .01f;
            dy = .02f * std::rand() / (float)RAND_MAX - .01f;
            variant = std::abs(dx) > 0.008;
        }
    };
    KeyboardController<float> kc{0.01};
    std::vector<__Dot> dots;
    SkPaint paint;
    SkPaint paint_line;
    int width;
    int height;
    int n;

    public:
    Dotfield(int _width, int _height, int _n):
        width(_width),
        height(_height),
        n(_n)
    {
        paint.setColor(SK_ColorWHITE);
        paint.setStyle(SkPaint::kStroke_Style);
        std::srand(std::time(nullptr));
        dots.push_back(__Dot(0,0,0,0)); // player
        for (int i = 0; i < n; i++)
            dots.push_back(__Dot());
    }

    private:
    void render(SkCanvas* _c) {
        for (auto dot : dots) {
            float _x = std::sin(dot.x) * std::cos(dot.y);
            float _y = std::sin(dot.x) * std::sin(dot.y);
            float _z = std::cos(dot.x);

            int x = (_x + 1) / 2 * width;
            int y = (_y + 1) / 2 * height;
            int z = (_z + 1) / 2 * 255;
            paint.setColor(0xff000055 | z | z << 8 | z << 16);
            if (dot.dx == 0)                  // dot is player
                _c->drawCircle(x, y, 5, paint);
            else if (dot.variant) // draw dot as circle
                _c->drawCircle(x, y, (1000 * dot.dx - 8), paint);
            else                              // draw dot as pixel
                _c->drawPoint(x, y, paint);
        }
    }
    void update(State* _s) {
        kc.update(_s);
        for (auto& dot : dots) {
            dot.x += kc.dx;
            dot.y += kc.dy;
            dot.x += dot.dx;
            dot.y += dot.dy;
        }
    }
    void handle_event(SDL_Event* _e) {
        kc.handle_event(_e);
    }
};