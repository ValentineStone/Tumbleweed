#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "SDL.h"
#include "tinyxml2.h"
#include "pugixml.hpp"

const int WIDTH = 255;
const int HEIGHT = 255;
const int FPS = 255;

/*
tinyxml2::XMLElement* query_selector(
    tinyxml2::XMLDocument& _doc,
    std::string _path
) {
    std::istringstream iss(_path);
    std::vector<std::string> names {
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>{}
    };
    tinyxml2::XMLNode* node = &_doc;
    for (auto name : names)
        if (!(node = node->FirstChildElement(name.c_str())))
            return nullptr;
    return node->ToElement();
}
*/

int main(int _argc, char** _argv) {
    bool is_running = false;
    SDL sdl("Hello, world!", WIDTH, HEIGHT);

    pugi::xml_document doc;
    auto result = doc.load_file("index.xml");

    try {
        auto t = doc.select_node("/terminal/output/display/@width");
        std::cout << t.attribute().value();
    }
    catch (pugi::xpath_exception& e) {
        std::cout << e.what();
    }

    std::cout
        << "Load result: "
        << result.description()
        << ", display width: "
        << NULL

        << std::endl;

    /*
    tinyxml2::XMLDocument doc;
	doc.LoadFile("index.xml");
    tinyxml2::XMLElement* elem = query_selector(doc, "terminal output display");
    if (elem) {
        int width;
        if (!elem->QueryIntAttribute("width", &width))
            std::cout << "width=" << width << '\n';
        else
            std::cout << "element has no width attribute\n";
    }
    else
        std::cout << "the path is incorrect\n";
    */
    
    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                is_running = false;
        SDL_Delay(1000 / FPS);
    }

    return 0;
}