#include <iostream>
#include "Terminal.h"
#include "Game.h"

int main(int _argc, char** _argv) {
    bool is_running = false;
    Terminal terminal("program");
    Game game;
    terminal.__set_entity(&game);
    terminal.run();
    return 0;
}