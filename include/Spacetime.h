#pragma once
#include "tumbleweed.h"
#include "KeyboardController.h"

const float SQRT2 = 1.4142135623730950488016887242097;

class Spacetime: public Entity {
    KeyboardController<float> kc{0.01};
    std::vector<Vector3d> dots;
    SkPaint paint;
    int off_x;
    int off_y;
    float r2 = 30;

    public:
    Spacetime(float _r2): r2(_r2) {
        dots.push_back({  r2,  r2,  r2 });
        dots.push_back({  r2,  r2, -r2 });
        dots.push_back({  r2, -r2,  r2 });
        dots.push_back({  r2, -r2, -r2 });
        dots.push_back({ -r2,  r2,  r2 });
        dots.push_back({ -r2,  r2, -r2 });
        dots.push_back({ -r2, -r2,  r2 });
        dots.push_back({ -r2, -r2, -r2 });
        paint.setColor(SK_ColorWHITE);
        paint.setStyle(SkPaint::kStroke_Style);
        paint.setAntiAlias(true);
    }
    void render(SkCanvas* _c) {
        for (auto dot : dots)
                _c->drawPoint(dot.x + off_x, dot.y + off_y, paint);
        for (int i = 0; i < dots.size(); i++)
            for (int j = i + 1; j < dots.size(); j++) {
                int c = (dots[i].z + (dots[j].z - dots[i].z) / 2) / r2 / SQRT2 * 127 + 128;
                paint.setColor(0xff000055 | c | c << 8 | c << 16);
                _c->drawLine(
                    dots[i].x + off_x,
                    dots[i].y + off_y,
                    dots[j].x + off_x,
                    dots[j].y + off_y,
                    paint
                );
            }
    }
    void update(State* _s) {
        kc.update(_s);
        if (kc.dx == 0) kc.dx = kc.vel;
        if (kc.dy == 0) kc.dy = kc.vel * 0.5;
        off_x = _s->screen_w / 2;
        off_y = _s->screen_h / 2;

        for (auto& dot : dots) {
            dot.y =  std::cos(kc.dx) * dot.y - std::sin(kc.dx) * dot.z;
            dot.z =  std::sin(kc.dx) * dot.y + std::cos(kc.dx) * dot.z;

            dot.x =  std::cos(kc.dy) * dot.x + std::sin(kc.dy) * dot.z;
            dot.z = -std::sin(kc.dy) * dot.x + std::cos(kc.dy) * dot.z;
        }

    }
    void handle_event(SDL_Event* _e) {
        kc.handle_event(_e);
    }
};