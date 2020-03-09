workspace "tumbleweed"
    configurations { "Debug", "Release" }

project "tumbleweed"
    kind "WindowedApp"
    language "C++"
    files {
        "src/**.cpp",
    }
    includedirs {
        "skia_include",
        "include"
    }
    libdirs { "lib" }
    links {
        "tinyxml2",
        "SDL2",
        "SDL2main",
        "skia",
        "User32",
    }
    targetdir "."
    linkoptions { "-Xlinker -subsystem:windows" }
    symbols "On"

    filter "configurations:Debug"
        defines { "DEBUG" }

    filter "configurations:Release"
        optimize "On"