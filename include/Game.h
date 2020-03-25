#pragma once
#include "tumbleweed.h"
#include "Spacetime.h"

class Game: public Container {
    Spacetime Spacetime{128};

    public:
    Game() {
        add(&Spacetime);
    }
    private:
    void render(SkCanvas* _c) {
        _c->clear(0xff020205);
        Container::render(_c);
    }
};