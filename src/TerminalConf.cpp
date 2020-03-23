#include "TerminalConf.h"

template<>
void TerminalConf::load<1,0> (path_t _root) {
    auto index_path = _root / "index.xml";
    pugi::xml_document doc;
    doc.load_file(index_path.c_str());
    auto term = doc.child("terminal");
    float float_version = term.attribute("version").as_float();
    int version = (int)float_version;
    int subversion = (int)(float_version * 10) % 10;
    switch (version) {
        case 1:
            auto config = term.child("options");
            width = config.attribute("width").as_int();
            height = config.attribute("height").as_int();
            fps = config.attribute("fps").as_int();
            title = config.attribute("title").as_string();
            fullscreen = config.attribute("fullscreen").as_bool();
            icon_path = _root / config.attribute("icon").as_string();
    }
}

template<>
void TerminalConf::load<2,0> (path_t _root) {
    auto index_path = _root / "index.lua";
    sol::state lua;
    lua.script_file(index_path.generic_string());
    width = lua["config"]["width"];
    height = lua["config"]["height"];
    fps = lua["config"]["fps"];
    fullscreen = lua["config"]["fullscreen"];
    title = lua["config"]["title"];
    icon_path = _root / (std::string)lua["config"]["icon"];
}

TerminalConf::operator std::string() const {
    std::stringstream ss;
    ss  << "TerminalConf("
        << "\n\twidth: "      << width
        << "\n\theight: "     << height
        << "\n\tfps: "        << fps
        << "\n\tfullscreen: " << (fullscreen ? "true" : "false")
        << "\n\ttitle: "      << title
        << "\n\ticon_path: "  << icon_path
        << "\n)";
    return ss.str();
}

std::ostream& operator <<(std::ostream& o, const TerminalConf& tc) {
    return o << (std::string)tc;
}