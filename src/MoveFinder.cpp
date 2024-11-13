/*
** EPITECH PROJECT, 2024
** B-AIA-500-REN-5-1-gomoku-hugues.lejeune
** File description:
** MoveFinder
*/

#include "MoveFinder.hpp"

MoveFinder::MoveFinder(std::vector<std::vector<int>> board, int boardSize) : _board(board), _boardSize(boardSize), _depth(0)
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
            scores[x][y] = findMoveScore(x, y, true);
            _board[x][y] = Piece::PLAYER;
            scores[x][y] -= findOpponentBestNextMove();
            _board[x][y] = Piece::EMPTY;
        }
    }
    return findGreatestScore(scores);
}


int MoveFinder::findOpponentBestNextMove(void)
{
    std::vector<std::vector<int>> scores(_boardSize, std::vector<int>(_boardSize, 0));

    for (int x = 0; x < _boardSize; x++) {
        for (int y = 0; y < _boardSize; y++) {
            if (_board[x][y] != Piece::EMPTY) {
                continue;
            }
            scores[x][y] = findMoveScore(x, y, false);
        }
    }

    std::vector<int> greatest_pos = findGreatestScore(scores);

    return scores[greatest_pos[0]][greatest_pos[1]];
}


int MoveFinder::findMoveScore(int x, int y, bool isPlayer)
{
    int score = 0;

    for (int i = 0; i < 4; i++) {
        score += evaluateDirection(x, y, static_cast<Direction>(i), isPlayer);
    }

    return score;
}


std::vector<int> MoveFinder::findGreatestScore(std::vector<std::vector<int>> scores)
{
    int greatest;
    std::vector<std::vector<int>> greatest_pos;
    std::size_t index;

    // Find the greatest score
    for (int x = 0; x < _boardSize; x++) {
        for (int y = 0; y < _boardSize; y++) {
            if (x == 0 && y == 0) {
                greatest = scores[x][y];
                continue;
            }
            if (_board[x][y] == Piece::EMPTY && scores[x][y] > greatest) {
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


int MoveFinder::evaluateDirection(int x, int y, Direction direction, bool isPlayer)
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
            if ((isPlayer && _board[x_pos][y_pos] == Piece::PLAYER) || (!isPlayer && _board[x_pos][y_pos] == Piece::OPPONENT)) {
                pieces_count++;
            }
            if ((isPlayer && _board[x_pos][y_pos] == Piece::OPPONENT) || (!isPlayer && _board[x_pos][y_pos] == Piece::PLAYER)) {
                pieces_count = 0;
                break;
            }
        }

        score += evaluateScore(pieces_count, isPlayer);
    }

    return score;
}


int MoveFinder::evaluateScore(int pieces_count, bool isPlayer)
{
    switch (pieces_count) {
        case 0:
            return isPlayer ? Scores::PLAYER_ONE_IN_A_ROW : Scores::OPPONENT_ONE_IN_A_ROW;
        case 1:
            return isPlayer ? Scores::PLAYER_TWO_IN_A_ROW : Scores::OPPONENT_TWO_IN_A_ROW;
        case 2:
            return isPlayer ? Scores::PLAYER_THREE_IN_A_ROW : Scores::OPPONENT_THREE_IN_A_ROW;;
        case 3:
            return isPlayer ? Scores::PLAYER_FOUR_IN_A_ROW : Scores::OPPONENT_FOUR_IN_A_ROW;;
        case 4:
            return isPlayer ? Scores::PLAYER_FIVE_IN_A_ROW : Scores::OPPONENT_FIVE_IN_A_ROW;;
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
