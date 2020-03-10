#pragma once
#include <SDL2/SDL.h>
#include <Skia.h>


namespace tw {

#define tw_color(_COLOR) SK_Color##_COLOR
typedef SDL_Event event_t;
typedef SkCanvas canvas_t;
typedef SkPaint paint_t;
typedef struct {} state_t;

struct entity_t {
    virtual void render(canvas_t*) = 0;
    virtual void update(state_t*) = 0;
    virtual void handle_event(event_t*) = 0;
};

}