#include <SDL2/SDL.h>
#include <vector>

using namespace std;

#define GridSize 15
enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Game
{
    public:
        void Init(const char* title, int w, int h);
        Direction currentDirection;
        int score;
        int highscore;
        SDL_Window* window;
        SDL_Renderer* renderer;
        int frameRate;
    private:
        vector<SDL_Rect> snake;
        SDL_Rect map;
        SDL_Rect apple;
        SDL_Event currentEvent;
        bool pause;
        bool running;
        bool isDead;
        double deltaTime;
        void Start();
        void Update();
        void GameLoop();
        void Events();
        void RenderAll();
        void UpdateTitle(); 
        void Eat();
        void Grow();
        void Die();
        void SpawnApple();
};