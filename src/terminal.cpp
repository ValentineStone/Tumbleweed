#include "terminal.h"
#include <iostream>
#include <pugixml.hpp>

namespace tw {

SDL_Surface* __get_icon();

terminal::terminal(std::filesystem::path _program_path) {
    program_path = _program_path;
    init_with_program_path();
    init_sdl();
    init_skia();
}

void terminal::render() {
    render_sdl();
}
void terminal::update() {
    entity->update(&state);
}
void terminal::run() {
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

void terminal::__set_entity(entity_t* _entity) {
    entity = _entity;
}

void terminal::init_skia() {
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

void terminal::init_sdl() {
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
terminal::~terminal() {
    free_skia();
    free_sdl();
}
void terminal::free_sdl() {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
void terminal::free_skia() {
    SDL_FreeSurface(sk_sdl_surface);
}
void terminal::render_sdl() {
    SDL_RenderClear(ren);
    render_skia();
    SDL_RenderPresent(ren);
}
void terminal::render_skia() {
    entity->render(sk_canvas);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, sk_sdl_surface);
    if (tex == nullptr)
        handle_error_sdl("SDL_CreateTextureFromSurface");
    SDL_RenderCopy(ren, tex, nullptr, nullptr);
    SDL_DestroyTexture(tex);
}


void terminal::handle_error_sdl(std::string _msg) {
    std::cerr << _msg << ": " << SDL_GetError() << std::endl;
    std::cout << _msg << ": " << SDL_GetError() << std::endl;
}

void terminal::init_with_program_path() {
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




SDL_Surface* __get_icon() {
    SDL_Surface *surface;     // Declare an SDL_Surface to be filled in with pixel data from an image file
    Uint16 pixels[16*16] = {  // ...or with raw pixel data:
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
    0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
    0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
    0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
    0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
    0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
    0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
    0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
    0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
    0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
    0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
    0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
    0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
    0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
    0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
    0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
    0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
    0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
    0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
    0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
    0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
    0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
    };
    surface = SDL_CreateRGBSurfaceFrom(pixels,16,16,16,16*2,0x0f00,0x00f0,0x000f,0xf000);
    return surface;
}

}