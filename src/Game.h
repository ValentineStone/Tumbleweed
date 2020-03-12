#pragma once
#include "tumbleweed.h"
#include "Player.h"
#include "Dotfield.h"

class Game: public Container {
    Player player{100,100};
    Dotfield dotfield{255,255,1000};

    public:
    Game() {
        entities.push_back(&player);
        entities.push_back(&dotfield);
    }
    private:
    void render(SkCanvas* _c) {
        _c->clear(0xff020205);
        Container::render(_c);
    }
};