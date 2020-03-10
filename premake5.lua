workspace "tumbleweed"
    configurations { "Debug", "Release" }

project "tumbleweed"
    kind "WindowedApp"
    language "C++"
    cppdialect "c++17"
    files {
        "src/**.cpp",
    }
    includedirs {
        "skia_include",
        "include"
    }
    libdirs { "lib" }
    links {
        "pugixml",
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
        buildoptions { "--debug" }

    filter "configurations:Release"
        optimize "On"