#include "Game.h"
#include "App.h"
#include <SDL2/SDL.h>
#include <ctime>
#include <cstdlib>

Game::Game()
{
    srand(time(NULL)); // generate new seed
    restartGame();
}

void Game::update(SDL_Event *event)
{

}
void Game::render() const
{
    SDL_SetRenderDrawColor(App::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(App::getRenderer());

    board.render();

    SDL_RenderPresent(App::getRenderer());
}

void Game::checkWin()
{
    if(board.hasWinner() || board.isDraw())
        state = STATE_STOPPED;
}

