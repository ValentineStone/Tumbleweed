#pragma once
#include "tumbleweed.h"
#include "TerminalConf.h"

class Terminal {
    public: 
    Terminal(std::filesystem::path);
    ~Terminal();
    void run();
    void render();
    void update();
    void __set_entity(Entity*);

    private:
    TerminalConf conf;
    std::filesystem::path program_path;
    SDL_Window* win;
    SDL_Renderer* ren;
    
    SDL_Surface* sk_sdl_surface;
    SkImageInfo sk_image_info;
    sk_sp<SkSurface> sk_surface;
    SkCanvas* sk_canvas;


    Entity* entity;
    State state;
        
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
