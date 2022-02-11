#include <iostream>
#include <SDL2/SDL.h>
#include "game.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    Game game;
    game.Init("Snake", 510, 510);
    return 0;
}
