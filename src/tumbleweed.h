#pragma once
#include <SDL2/SDL.h>
#include <Skia.h>
#include <vector>

typedef SDL_Event SDL_Event;
typedef SkCanvas SkCanvas;
typedef SkPaint SkPaint;
typedef struct {
} State;

struct Entity {
    virtual void render(SkCanvas*) = 0;
    virtual void update(State*) = 0;
    virtual void handle_event(SDL_Event*) = 0;
};

struct Container: public Entity {
    std::vector<Entity*> entities;
    virtual void render(SkCanvas* _c) {
        for (auto e : entities)
            e->render(_c);
    }
    virtual void update(State* _s) {
        for (auto e : entities)
            e->update(_s);
    }
    virtual void handle_event(SDL_Event* _e) {
        for (auto e : entities)
            e->handle_event(_e);
    }
};