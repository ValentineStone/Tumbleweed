#pragma once
#include <filesystem>
#include <iostream>
#include <string>


struct TerminalConf {
    static constexpr int __LATEST_VER = 2;
    static constexpr int __LATEST_SUB = 0;

    typedef std::filesystem::path path_t;

    int width;
    int height;
    int fps;
    bool fullscreen;
    std::string title;
    path_t icon_path;
    
    template <int VER = __LATEST_VER, int SUB = __LATEST_SUB>
    void load(path_t);

    operator std::string() const;
};

std::ostream& operator <<(std::ostream&, const TerminalConf&);