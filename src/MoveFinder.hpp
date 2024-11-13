/*
** EPITECH PROJECT, 2024
** B-AIA-500-REN-5-1-gomoku-hugues.lejeune
** File description:
** MoveFinder
*/

#ifndef MOVEFINDER_HPP_
#define MOVEFINDER_HPP_

#include <stdexcept>
#include <vector>

class MoveFinder
{
    public:
        MoveFinder(std::vector<std::vector<int>> board, int boardSize);
        ~MoveFinder() = default;

        std::vector<int> findBestMove(void);

    protected:
    private:
        enum Piece {
            EMPTY = 0,
            PLAYER = 1,
            OPPONENT = 2
        };

        enum Direction {
            HORIZONTAL = 0,
            VERTICAL = 1,
            DIAGONAL = 2,
            ANTI_DIAGONAL = 3
        };

        std::vector<std::vector<int>> _board;
        int _boardSize;

        int findMoveScore(int x, int y);
        std::vector<int> findGreatestScore(std::vector<std::vector<int>> scores);

        int evaluateDirection(int x, int y, Direction direction);

        void getOffset(Direction direction, int &x_offset, int &y_offset);
};

#endif /* !MOVEFINDER_HPP_ */
