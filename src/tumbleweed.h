#pragma once
#include <SDL2/SDL.h>
#include <Skia.h>

typedef SDL_Event SDL_Event;
typedef SkCanvas SkCanvas;
typedef SkPaint SkPaint;
typedef struct {} State;

struct Entity {
    virtual void render(SkCanvas*) = 0;
    virtual void update(State*) = 0;
    virtual void handle_event(SDL_Event*) = 0;
};