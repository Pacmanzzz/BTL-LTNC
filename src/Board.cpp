#include "Board.h"
#include "App.h"
#include "Util.h"

Board::Board() { restart(); }

void Board::render() const
{
    SDL_SetRenderDrawColor(App::getRenderer(), 0x00, 0x00, 0x00, 0xFF);

    renderBoard();
    renderPieces();
}

void Board::restart()
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            m[i][j] = PIECE_EMPTY;

    occupiedPlaces = 0;
}

bool Board::hasWinner() const
{
    return (checkRows() || checkColumns() || checkDiagonals());
}

bool Board::isDraw() const
{
    return occupiedPlaces == 9;
}

void Board::place(int row, int col, bool humanPiece)
{
    if(row>=0 && row<3 && col>=0 && col<3 && occupiedPlaces<9)
    {
        m[row][col] = humanPiece ? PIECE_X : PIECE_O;
        occupiedPlaces++;
    }
}

bool Board::isFieldEmpty(int row, int col) const
{
    if(row>=0 && row<3 && col>=0 && col<3)
        return m[row][col] == PIECE_EMPTY;

    return false;
}

bool Board::isFieldCross(int row, int col) const
{
    if(row>=0 && row<3 && col>=0 && col<3)
        return m[row][col] == PIECE_X;

    return false;
}

bool Board::isFieldCircle(int row, int col) const
{
    if(row>=0 && row<3 && col>=0 && col<3)
        return m[row][col] == PIECE_O;

    return false;
}

void Board::renderBoard() const
{
    SDL_RenderDrawLine(App::getRenderer(),
        App::SCREEN_WIDTH/3, 0,
        App::SCREEN_WIDTH/3, App::SCREEN_HEIGHT);

    SDL_RenderDrawLine(App::getRenderer(),
        App::SCREEN_WIDTH/3*2, 0,
        App::SCREEN_WIDTH/3*2, App::SCREEN_HEIGHT);

    SDL_RenderDrawLine(App::getRenderer(),
        0, App::SCREEN_HEIGHT/3,
        App::SCREEN_WIDTH, App::SCREEN_HEIGHT/3);

    SDL_RenderDrawLine(App::getRenderer(),
        0, App::SCREEN_HEIGHT/3*2,
        App::SCREEN_WIDTH, App::SCREEN_HEIGHT/3*2);
}

void Board::renderPieces() const
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            switch(m[i][j])
            {
                case PIECE_X:
                    Util::drawCross(i, j); break;
                case PIECE_O:
                    Util::drawCircle(i, j); break;
                default:
                    break;
            }
        }
}

bool Board::checkRows() const
{
    if(m[0][0] == m[0][1] && m[0][1] == m[0][2] && !isFieldEmpty(0,2))
        return true;
    else if(m[1][0] == m[1][1] && m[1][1] == m[1][2] && !isFieldEmpty(1,2))
        return true;
    else if(m[2][0] == m[2][1] && m[2][1] == m[2][2] && !isFieldEmpty(2,2))
        return true;

    return false;
}

bool Board::checkColumns() const
{
    if(m[0][0] == m[1][0] && m[1][0] == m[2][0] && !isFieldEmpty(2,0))
        return true;
    else if(m[0][1] == m[1][1] && m[1][1] == m[2][1] && !isFieldEmpty(2,1))
        return true;
    else if(m[0][2] == m[1][2] && m[1][2] == m[2][2] && !isFieldEmpty(2,2))
        return true;

    return false;
}

bool Board::checkDiagonals() const
{
    if(m[0][0] == m[1][1] && m[1][1] == m[2][2] && !isFieldEmpty(2,2))
        return true;
    else if(m[0][2] == m[1][1] && m[1][1] == m[2][0] && !isFieldEmpty(2,0))
        return true;

    return false;
}
