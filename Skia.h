#include <SDL2/SDL.h>
#include <Skia.h>
#include <iostream>
#include <functional>

#ifndef __TUMBLEWEED_SKIA_H
#define __TUMBLEWEED_SKIA_H
struct Skia {
    SDL_Surface* sdl_surface;
    SkImageInfo sk_image_info;
    sk_sp<SkSurface> sk_surface;
    SkCanvas* sk_canvas;
    int width;
    int height;
    Skia(int _width, int _height) {
        width = _width;
        height = _height;
        sdl_surface = SDL_CreateRGBSurfaceWithFormat(
            0,
            _width,
            _height,
            32,
            SDL_PIXELFORMAT_BGRA32
        );
        if (sdl_surface == NULL) 
            std::cout << "SDL_CreateRGBSurfaceWithFormat() failed: " << SDL_GetError();

        sk_image_info = SkImageInfo::MakeN32Premul(_width, _height);
        sk_surface = SkSurface::MakeRasterDirect(
            sk_image_info,
            sdl_surface->pixels,
            sdl_surface->pitch
        );
        sk_canvas = sk_surface->getCanvas();
    }
    ~Skia() {
        if (sdl_surface)
            SDL_FreeSurface(sdl_surface);
    }
    void draw(SDL_Renderer* _ren, std::function<void(SkCanvas*)> _draw) {
        _draw(sk_canvas);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(_ren, sdl_surface);
        if (tex == nullptr)
            std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_RenderCopy(_ren, tex, nullptr, nullptr);
        SDL_DestroyTexture(tex);
    }
};
#endif//__TUMBLEWEED_SKIA_H