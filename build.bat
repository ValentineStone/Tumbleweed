@echo off
del tumbleweed.exe
premake5 gmake2
make SHELL=cmd
tumbleweed.exe > stdout.log 2> stderr.log