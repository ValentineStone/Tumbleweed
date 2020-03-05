#include <iostream>
#include "SDL.h"

SDL::SDL(const char* _title, int _width, int _height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;

    this->win = SDL_CreateWindow(_title, 100, 100, _width, _height, SDL_WINDOW_SHOWN);
    if (this->win == nullptr)
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

    this->ren = SDL_CreateRenderer(
        this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->ren == nullptr)
        std::cout << "SDL_CreateRenderer Error" << SDL_GetError() << std::endl;
}
SDL::~SDL() {
    SDL_DestroyRenderer(this->ren);
    SDL_DestroyWindow(this->win);
    SDL_Quit();
}
void SDL::draw(std::function<void(SDL_Renderer*, SDL_Window*)> _drawfunc) {
    SDL_RenderClear(this->ren);
    _drawfunc(this->ren, this->win);
    SDL_RenderPresent(this->ren);
}
void SDL::draw(std::function<void(SDL_Renderer*)> _drawfunc) {
    SDL_RenderClear(this->ren);
    _drawfunc(this->ren);
    SDL_RenderPresent(this->ren);
}
void SDL::draw(std::function<void()> _drawfunc) {
    SDL_RenderClear(this->ren);
    _drawfunc();
    SDL_RenderPresent(this->ren);
}