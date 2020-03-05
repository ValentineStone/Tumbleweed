@echo off
del tumbleweed.exe
premake5 gmake2
make CXX=clang++ SHELL=cmd