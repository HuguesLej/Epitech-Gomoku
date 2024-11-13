/*
** EPITECH PROJECT, 2024
** B-AIA-500-REN-5-1-gomoku-hugues.lejeune
** File description:
** MoveFinder
*/

#include "MoveFinder.hpp"

MoveFinder::MoveFinder(std::vector<std::vector<int>> board, int boardSize) : _board(board), _boardSize(boardSize)
{
}

std::vector<int> MoveFinder::findBestMove(void)
{
    std::vector<std::vector<int>> scores(_boardSize, std::vector<int>(_boardSize, 0));

    for (int x = 0; x < _boardSize; x++) {
        for (int y = 0; y < _boardSize; y++) {
            if (_board[x][y] != 0) {
                continue;
            }
            scores[x][y] = findMoveScore(x, y);
        }
    }
    return findGreatestScore(scores);
}

int MoveFinder::findMoveScore(int x, int y)
{
    if (_board[x][y] == 0) {
        return 1;
    }
    return 0;
}

std::vector<int> MoveFinder::findGreatestScore(std::vector<std::vector<int>> scores)
{
    int greatest = 0;
    std::vector<std::vector<int>> greatest_pos;
    std::size_t index;

    // Find the greatest score
    for (int x = 0; x < _boardSize; x++) {
        for (int y = 0; y < _boardSize; y++) {
            if (scores[x][y] > greatest) {
                greatest = scores[x][y];
            }
        }
    }

    // Put all the greatest scores in a vector
    for (int x = 0; x < _boardSize; x++) {
        for (int y = 0; y < _boardSize; y++) {
            if (scores[x][y] == greatest) {
                greatest_pos.push_back({x, y});
            }
        }
    }

    // Return a random greatest score
    index = rand() % greatest_pos.size();
    return greatest_pos[index];
}
