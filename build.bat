@echo off
title Build
echo Compiling
g++ main.cpp .\src\* -Iinclude\ -o Snake -IC:\SDL2\x86_64-w64-mingw32\include -LC:\SDL2\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2
color 0a
pause
exit