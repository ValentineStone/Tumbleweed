#include "Terminal.h"
#include <iostream>

Terminal::Terminal(std::filesystem::path _program_path) {
    program_path = _program_path;
    conf.load<2,0>(_program_path);
    std::cerr << conf;
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
        SDL_Delay(1000 / conf.fps);
    }
}

void Terminal::__set_entity(Entity* _entity) {
    entity = _entity;
}

void Terminal::init_skia() {
    sk_sdl_surface = SDL_CreateRGBSurfaceWithFormat(
        0,
        conf.width,
        conf.height,
        32,
        SDL_PIXELFORMAT_BGRA32
    );
    if (sk_sdl_surface == nullptr) 
        handle_error_sdl("SDL_CreateRGBSurfaceWithFormat");

    sk_image_info = SkImageInfo::MakeN32Premul(conf.width, conf.height);
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
        conf.title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        conf.width, conf.height,
        SDL_WINDOW_SHOWN
        | (conf.fullscreen ? SDL_WINDOW_FULLSCREEN : 0)
    );
    if (this->win == nullptr)
        handle_error_sdl("SDL_CreateWindow");

    auto icon = SDL_LoadBMP(conf.icon_path.generic_string().c_str());
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