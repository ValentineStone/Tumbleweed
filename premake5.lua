workspace "tumbleweed"
    configurations { "Debug", "Release" }

project "tumbleweed"
    kind "WindowedApp"
    language "C++"
    files {
        "src/**.cpp",
        "src/**.pch",
    }
    includedirs {
        "skia_include",
        "include"
    }

    buildoptions {
        "-std=c++2a",
        "-include-pch obj/tumbleweed.pch"
    }
    defines { "USES_TUMBLEWEED_PCH" }

    libdirs { "lib" }
    links {
        "lua54",
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