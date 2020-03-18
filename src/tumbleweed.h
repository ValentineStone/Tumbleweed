#pragma once
#ifndef USES_TUMBLEWEED_PCH
#include <SDL2/SDL.h>
#include <Skia.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <filesystem>
#include <string>
#include <pugixml.hpp>
#include <sol/sol.hpp>

struct State {};

class Entity {
    public:
    virtual void render(SkCanvas*) {}
    virtual void update(State*) {}
    virtual void handle_event(SDL_Event*) {}
};

class Container: public Entity {
    std::vector<Entity*> entities;
    std::vector<Entity*> additions;
    std::vector<Entity*> deletions;
    public:
    void add(Entity* _e) {
        additions.push_back(_e);
    }
    void del(Entity* _e) {
        deletions.push_back(_e);
    }
    virtual void render(SkCanvas* _c) {
        for (auto e : entities)
            e->render(_c);
    }
    virtual void update(State* _s) {
        entities.insert(entities.end(), additions.begin(), additions.end());
        for (const auto& v : deletions)
            entities.erase(
                std::remove(entities.begin(), entities.end(), v),
                entities.end()
            );
        additions.clear();
        deletions.clear();
        for (auto e : entities)
            e->update(_s);
    }
    virtual void handle_event(SDL_Event* _e) {
        for (auto e : entities)
            e->handle_event(_e);
    }
};
#endif