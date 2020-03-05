#include <SDL2/SDL.h>
#include <functional>

#ifndef _GAMEPP_SDL_HPP
#define _GAMEPP_SDL_HPP
struct SDL {
    SDL_Window* win;
    SDL_Renderer* ren;
    SDL(const char* _title, int _width, int _height);
    ~SDL();
    void draw(std::function<void(SDL_Renderer*, SDL_Window*)> _drawfunc);
    void draw(std::function<void(SDL_Renderer*)> _drawfunc);
    void draw(std::function<void()> _drawfunc);
};
#endif//_GAMEPP_SDL_HPP