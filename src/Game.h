#pragma once
#include "tumbleweed.h"
#include "Player.h"
#include "Dotfield.h"
#include <vector>

class Game: public Entity {
    Player player{100,100};
    Dotfield dotfield{255,255,1000};
    std::vector<Entity*> entities;
;
    public:
    Game() {
        entities.push_back(&player);
        entities.push_back(&dotfield);
    }
    private:
    void render(SkCanvas* _c) {
        _c->clear(0xff020205);
        for (auto e : entities)
            e->render(_c);
    }
    void update(State* _s) {
        for (auto e : entities)
            e->update(_s);
    }
    void handle_event(SDL_Event* _e) {
        for (auto e : entities)
            e->handle_event(_e);
    }
};