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
    int score = 0;

    for (int i = 0; i < 4; i++) {
        score += evaluateDirection(x, y, static_cast<Direction>(i));
    }

    return score;
}


#include <iostream>
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

    std::cout << "DEBUG ============================== Start Debugging ==============================" << std::endl;
    std::cout << "DEBUG Greatest score: " << greatest << std::endl;
    for (auto &pos : greatest_pos) {
        std::cout << "DEBUG (" << pos[0] << "," << pos[1] << ")" << std::endl;
    }

    // Return a random greatest score
    index = rand() % greatest_pos.size();
    std::cout << "DEBUG Play (" << greatest_pos[index][0] << ", " << greatest_pos[index][1] << ")" << std::endl;
    std::cout << "DEBUG =============================== End Debugging ===============================" << std::endl;
    return greatest_pos[index];
}


int MoveFinder::evaluateDirection(int x, int y, Direction direction)
{
    int pieces_count = 0;
    int x_offset = 0;
    int y_offset = 0;
    int score = 0;

    getOffset(direction, x_offset, y_offset);

    for (int i = -4; i < 1; i++) {
        pieces_count = 0;

        for (int j = i; j < i + 5; j++) {
            int x_pos = x + j * x_offset;
            int y_pos = y + j * y_offset;

            if (isOutOfBounds(x_pos, y_pos)) {
                continue;
            }
            if (_board[x_pos][y_pos] == Piece::PLAYER) {
                pieces_count++;
            }
            if (_board[x_pos][y_pos] == Piece::OPPONENT) {
                pieces_count = 0;
                break;
            }
        }

        score += evaluateScore(pieces_count);
    }

    return score;
}


int MoveFinder::evaluateScore(int pieces_count)
{
    switch (pieces_count) {
        case 0:
            return 1;
        case 1:
            return 10;
        case 2:
            return 100;
        case 3:
            return 1000;
        case 4:
            return 10000;
    }
    return 0;
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


bool MoveFinder::isOutOfBounds(int x, int y)
{
    return x < 0 || x >= _boardSize || y < 0 || y >= _boardSize;
}
