#include <SDL2/SDL.h>

SDL_Rect CreateRect(int x, int y, int w, int h)
{
    SDL_Rect output;
    output.x = x;
    output.y = y;
    output.w = w;
    output.h = h;
    return output;
}