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
            if (_board[x][y] != Piece::EMPTY) {
                continue;
            }
            scores[x][y] = findMoveScore(x, y);
        }
    }
    return findGreatestScore(scores);
}


int MoveFinder::findMoveScore(int x, int y)
{
    int score = 1;

    for (int i = 0; i < 4; i++) {
        score += evaluateDirection(x, y, static_cast<Direction>(i));
    }

    return score;
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


int MoveFinder::evaluateDirection(int x, int y, Direction direction)
{
    int score = 0;
    int x_offset = 0;
    int y_offset = 0;

    getOffset(direction, x_offset, y_offset);

    for (int i = 1; i < 5; i++) {
        if (x + i * x_offset >= _boardSize || y + i * y_offset >= _boardSize) {
            break;
        }
        if (_board[x + i * x_offset][y + i * y_offset] == Piece::PLAYER) {
            score++;
        } else {
            break;
        }
    }

    return score;
}


void MoveFinder::getOffset(Direction direction, int &x_offset, int &y_offset)
{
    switch (direction) {
        case Direction::HORIZONTAL:
            x_offset = 1;
            break;
        case Direction::VERTICAL:
            y_offset = 1;
            break;
        case Direction::DIAGONAL:
            x_offset = 1;
            y_offset = 1;
            break;
        case Direction::ANTI_DIAGONAL:
            x_offset = 1;
            y_offset = -1;
            break;
    }
}
