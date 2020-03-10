#pragma once
#include "tumbleweed.h"
#include "player.hpp"
#include "dotfield.hpp"
#include <vector>

namespace game {

class game_t: public tw::entity_t {
    game::player_t player{100,100};
    game::dotfield_t dotfield{255,255,1};
    std::vector<tw::entity_t*> entities;
;
    public:
    game_t() {
        entities.push_back(&player);
        entities.push_back(&dotfield);
    }
    private:
    void render(tw::canvas_t* _c) {
        //_c->clear(0xff050510);
        for (auto e : entities)
            e->render(_c);
    }
    void update(tw::state_t* _s) {
        for (auto e : entities)
            e->update(_s);
    }
    void handle_event(tw::event_t* _e) {
        for (auto e : entities)
            e->handle_event(_e);
    }
};

}