#include "Util.h"
#include "App.h"
#include <cmath>

void Util::drawCross(int row, int col)
{
    int fieldW = App::SCREEN_WIDTH/3;
    int fieldH = App::SCREEN_HEIGHT/3;

    SDL_RenderDrawLine(App::getRenderer(),
        col*fieldW, row*fieldH,
        col*fieldW+fieldW, row*fieldH+fieldH);

    SDL_RenderDrawLine(App::getRenderer(),
        col*fieldW, row*fieldH+fieldH,
        col*fieldW+fieldW, row*fieldH);
}

void Util::drawCircle(int row, int col)
{
    int fieldW = App::SCREEN_WIDTH/3;
    int fieldH = App::SCREEN_HEIGHT/3;

    int centerX = col*fieldW+(fieldW/2);
    int centerY = row*fieldH+(fieldH/2);

    int r = fieldW/2;

    double step = 2*M_PI/30;
    int endX = centerX + r;
    int endY = centerY;

    for(double angle=0; angle<2*M_PI; angle+=step)
    {
        int startX = endX;
        int startY = endY;
        endX = r * cos(angle) + centerX;
        endY = r * sin(angle) + centerY;
        SDL_RenderDrawLine(App::getRenderer(), startX, startY, endX, endY);
    }
}
