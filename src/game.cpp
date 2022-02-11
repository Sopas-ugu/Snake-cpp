#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <windows.h>
#include "game.hpp"
#include "gamehelper.h"

using namespace std;

void Game::Init(const char* title, int w, int h)
{
    SetConsoleTitleA("Snake Logger");

    frameRate = 12;

    score = 0;
    highscore = 0;
    pause = false;

    if (frameRate == 0)
        cout << "warning: If the framerate is 0 the FPS will not be limited." << endl;

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        cout << "error starting SDL video: " << SDL_GetError() << endl;
    
    
    window = NULL;
    renderer = NULL;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);
    
    if (window == NULL)
        cout << "error creating the window: " << SDL_GetError() << endl;
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (renderer == NULL)
        cout << "error creating the renderer: " << SDL_GetError() << endl;
    
    running = true;

    map = CreateRect(GridSize, GridSize, GridSize * 32, GridSize * 32);

    Start();
    GameLoop();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Game::Start()
{
    score = 0;
    isDead = false;
    UpdateTitle();
    currentDirection = RIGHT;
    snake.clear();
    snake.push_back(CreateRect(GridSize * 5, GridSize * 5, GridSize, GridSize));
    for (int i = 1; i < 5; i++)
    {
        snake.push_back(CreateRect(GridSize * 5 - (GridSize * i), GridSize * 5, GridSize, GridSize));
    }
    SpawnApple();
}
void Game::SpawnApple()
{
    apple.x = GridSize * rand() % map.w;
    apple.y = GridSize * rand() % map.h;
    apple.w = GridSize;
    apple.h = GridSize;
}
void Game::UpdateTitle()
{
    string newtitle = "Snake | Score: " + to_string(score) + " | High Score: " + to_string(highscore) + (pause ? " | Paused":"") ;
    SDL_SetWindowTitle(window, newtitle.c_str());
}
void Game::Die()
{
    Start();
    cout << "You died" << endl;
}
void Game::Eat()
{
    score++;
    if (score > highscore)
        highscore = score;
    SpawnApple();
    UpdateTitle();
    Grow();
}
void Game::Grow()
{
    snake.push_back(snake.back());
}
void Game::Update()
{
    if (pause)
        return;
    vector<SDL_Rect> oldSnake = snake;
    switch (currentDirection)
    {
        case UP:
            snake[0].y -= GridSize;
            break;
        case DOWN:
            snake[0].y += GridSize;
            break;
        case LEFT:
            snake[0].x -= GridSize;
            break;
        case RIGHT:
            snake[0].x += GridSize;
            break;
    }
    for (int i = 1; i < snake.size(); i++)
        snake[i] = oldSnake[i - 1];

    if (snake[0].x > map.w)
        Die();
    else if (snake[0].x < map.x)
        Die();
    else if (snake[0].y > map.h)
        Die();
    else if (snake[0].y < map.y)
        Die();
    for (int i = 1; i < snake.size(); i++)
    {
        if (SDL_HasIntersection(&snake[0], &snake[i]))
        {
            Die();
        }
    }
    if (SDL_HasIntersection(&snake[0], &apple))
        Eat();
}
void Game::Events()
{
    while (SDL_PollEvent(&currentEvent))
    {
        switch (currentEvent.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (currentEvent.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        pause = !pause;
                        UpdateTitle();
                        break;
                    case SDLK_w:
                        currentDirection = UP;
                        break;
                    case SDLK_a:
                        currentDirection = LEFT;
                        break;
                    case SDLK_s:
                        currentDirection = DOWN;
                        break;
                    case SDLK_d:
                        currentDirection = RIGHT;
                        break;
                }
                break;
        }
    }
}
void Game::RenderAll()
{
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Map color

    SDL_RenderDrawRect(renderer, &map);

    SDL_SetRenderDrawColor(renderer, 146, 255, 65, 255); //Snake color

    for (SDL_Rect r : snake)
    {
        SDL_RenderFillRect(renderer, &r);
    }

    SDL_SetRenderDrawColor(renderer, 255, 65, 65, 255); //Apple color

    SDL_RenderFillRect(renderer, &apple);

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); //Background color

    SDL_RenderPresent(renderer);
}
void Game::GameLoop()
{
    Uint32 a = SDL_GetTicks();
    Uint32 b = SDL_GetTicks();
    deltaTime = 0;
    while (running)
    {
        a = SDL_GetTicks();
        deltaTime += a - b;
        Events();
        Update();
        RenderAll();
        if (frameRate != 0)
            SDL_Delay(1000 / frameRate - deltaTime);
        deltaTime = 0;
        b = SDL_GetTicks();
    }
}
