// Header file to hold Game class.
#ifndef GAME_H
#define GAME_H 1

#include "Puzzle.h"
using namespace std;

class Game
{
public:
    Game() {delete this;}
    Game(Puzzle);
    bool** getBoard() {return board;}
    void move(int, int);
    bool isWin();
    ~Game() // Will not delete puzzle class
private:
    Puzzle* puzzle; // Pointer to corresponding puzzle
    bool** board; // Active player board
};

Game::Game(Puzzle _puzzle)
{
    puzzle = _puzzle; // Set pointer

    // Initialize player board
    board = new bool*[puzzle.getRows()];
    for (int i = 0; i < puzzle.getRows(); i++)
    {
        board[i] = new bool[puzzle.getColumns()];
        for (int j = 0; j < puzzle.getColumns(); j++) board[i][j] = false;
    }
}

void Game::move(int row, int column)
{
    board[row][column] = !board[row][column];
}

bool Game::isWin()
{
    for (int i = 0; i < puzzle.getRows(); i++)
    {
        for (int j = 0; j < puzzle.getColumns(); j++)
        {
            if (board[]i[j] == puzzle.getSolutionByPoint(i, j));
            else return false;
        }
    }
    return true;
}

Game::~Game()
{
    puzzle = nullptr;
    for (int i = 0; i < numRows; i++) delete[] board[i];
    delete[] board;
}

#endif
