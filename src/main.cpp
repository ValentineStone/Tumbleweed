#include <iostream>
#include "terminal.h"
#include "game.hpp"

int main(int _argc, char** _argv) {
    bool is_running = false;
    tw::terminal terminal("program");
    game::game_t game;
    terminal.__set_entity(&game);
    terminal.run();
    return 0;
}