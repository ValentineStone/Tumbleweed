@echo off
del main.exe
clang++  src/*.cpp -o main.exe -Iskia_include -Iinclude -Llib -lSDL2 -lSDL2main -lskia -lUser32 -Xlinker -subsystem:windows
main.exe > run.log