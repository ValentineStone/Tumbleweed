#pragma once
#include "tumbleweed.h"
#include "Player.h"
#include "Dotfield.h"
#include "Experiment.h"

class Game: public Container {
    Player player{100,100};
    Dotfield dotfield{640,640,10000};
    Experiment experiment;

    public:
    Game() {
        add(&player);
        add(&dotfield);
        add(&experiment);
    }
    private:
    void render(SkCanvas* _c) {
        _c->clear(0xff020205);
        Container::render(_c);
    }
};