#pragma once
#include <filesystem>
#include <string>
#include <SDL2/SDL.h>
#include <Skia.h>
#include "tumbleweed.h"

namespace tw {

class terminal {
    public: 
    terminal(std::filesystem::path);
    ~terminal();
    void run();
    void render();
    void update();
    void __set_entity(entity_t*);

    private:
    SDL_Window* win;
    SDL_Renderer* ren;
    
    SDL_Surface* sk_sdl_surface;
    SkImageInfo sk_image_info;
    sk_sp<SkSurface> sk_surface;
    SkCanvas* sk_canvas;

    int width;
    int height;
    int fps;
    bool fullscreen;
    bool running;
    std::string title;
    std::filesystem::path program_path;
    std::filesystem::path icon_path;
    entity_t* entity;
    state_t state;
        
    void handle_error(std::string);
    void handle_error_sdl(std::string);
    
    void init_with_program_path();
    void init_sdl();
    void init_skia();
    void free_sdl();
    void free_skia();
    void render_sdl();
    void render_skia();
};
}
