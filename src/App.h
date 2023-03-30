#ifndef _APP_
#define _APP_

#include <SDL2/SDL.h>
#include "Game.h"

class App
{
public:
    static const int SCREEN_WIDTH = 600;
    static const int SCREEN_HEIGHT = 600;

    ~App();

    bool init();
    void run();

    static SDL_Window *getWindow();
    static SDL_Renderer *getRenderer();

private:
    Game game;

    static SDL_Window *gWindow;
    static SDL_Renderer *gRenderer;
    SDL_Event event;
};

#endif
