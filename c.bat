@echo off
del main.exe
clang++  main.cpp SDL.cpp -Iskia_include -Iinclude -Llib -lSDL2 -lSDL2main -lskia -lUser32 -o main.exe
main.exe > run.log