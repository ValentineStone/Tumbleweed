#pragma once
#include "tumbleweed.h"
#include "KeyboardController.h"

class Player: public Entity {
    public:
    int x;
    int y;
    int r = 5;
    KeyboardController<int> controller{1};
    SkPaint paint;

    Player(int _x, int _y): x(_x), y(_y) {
        paint.setColor(SK_ColorWHITE);
        paint.setStyle(SkPaint::kStroke_Style);
    }
    void render(SkCanvas* _c) {
        _c->drawCircle(x, y, r, paint);
    }
    void update(State* _s) {
        controller.update(_s);
        x += controller.dx;
        y += controller.dy;
    }
    void handle_event(SDL_Event* _e) {
        controller.handle_event(_e);
    }
};