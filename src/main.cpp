#include <iostream>
#include <fstream>
#include "Terminal.h"
#include "Game.h"

int main(int _argc, char** _argv) {
    Terminal terminal("program");
    Game game;
    terminal.__set_entity(&game);
    terminal.run();
    return 0;
}