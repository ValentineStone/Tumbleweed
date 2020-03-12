#include "Terminal.h"
#include <iostream>
#include <pugixml.hpp>

Terminal::Terminal(std::filesystem::path _program_path) {
    program_path = _program_path;
    init_with_program_path();
    init_sdl();
    init_skia();
}

void Terminal::render() {
    render_sdl();
}
void Terminal::update() {
    entity->update(&state);
}
void Terminal::run() {
    running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            entity->handle_event(&event);
        }
        update();
        render();
        SDL_Delay(1000 / fps);
    }
}

void Terminal::__set_entity(Entity* _entity) {
    entity = _entity;
}

void Terminal::init_skia() {
    sk_sdl_surface = SDL_CreateRGBSurfaceWithFormat(
        0,
        width,
        height,
        32,
        SDL_PIXELFORMAT_BGRA32
    );
    if (sk_sdl_surface == nullptr) 
        handle_error_sdl("SDL_CreateRGBSurfaceWithFormat");

    sk_image_info = SkImageInfo::MakeN32Premul(width, height);
    sk_surface = SkSurface::MakeRasterDirect(
        sk_image_info,
        sk_sdl_surface->pixels,
        sk_sdl_surface->pitch
    );
    sk_canvas = sk_surface->getCanvas();
}

void Terminal::init_sdl() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        handle_error_sdl("SDL_Init");

    this->win = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
        | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0)
    );
    if (this->win == nullptr)
        handle_error_sdl("SDL_CreateWindow");

    auto icon = SDL_LoadBMP(icon_path.generic_string().c_str());
    SDL_SetWindowIcon(win, icon);
    SDL_FreeSurface(icon);

    this->ren = SDL_CreateRenderer(
        this->win, -1,
        SDL_RENDERER_ACCELERATED
        | SDL_RENDERER_PRESENTVSYNC
    );
    if (this->ren == nullptr)
        handle_error_sdl("SDL_CreateRenderer");
}
Terminal::~Terminal() {
    free_skia();
    free_sdl();
}
void Terminal::free_sdl() {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
void Terminal::free_skia() {
    SDL_FreeSurface(sk_sdl_surface);
}
void Terminal::render_sdl() {
    SDL_RenderClear(ren);
    render_skia();
    SDL_RenderPresent(ren);
}
void Terminal::render_skia() {
    entity->render(sk_canvas);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, sk_sdl_surface);
    if (tex == nullptr)
        handle_error_sdl("SDL_CreateTextureFromSurface");
    SDL_RenderCopy(ren, tex, nullptr, nullptr);
    SDL_DestroyTexture(tex);
}


void Terminal::handle_error_sdl(std::string _msg) {
    std::cerr << _msg << ": " << SDL_GetError() << std::endl;
    std::cout << _msg << ": " << SDL_GetError() << std::endl;
}

void Terminal::init_with_program_path() {
    auto index_path = program_path / "index.xml";
    pugi::xml_document doc;
    doc.load_file(index_path.c_str());
    auto term = doc.child("terminal");
    float float_version = term.attribute("version").as_float();
    int version = (int)float_version;
    int subversion = (int)(float_version * 10) % 10;
    switch (version) {
        case 1:
            auto config = term.child("options");
            height = config.attribute("height").as_int();
            width = config.attribute("width").as_int();
            fps = config.attribute("fps").as_int();
            title = config.attribute("title").as_string();
            fullscreen = config.attribute("fullscreen").as_bool();
            icon_path = program_path / config.attribute("icon").as_string();
    }
}
