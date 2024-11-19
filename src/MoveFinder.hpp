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

#define MAX_DEPTH 2

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

        enum Scores {
            PLAYER_ONE_IN_A_ROW = 10,
            PLAYER_TWO_IN_A_ROW = 100,
            PLAYER_THREE_IN_A_ROW = 1000,
            PLAYER_FOUR_IN_A_ROW = 10000,
            PLAYER_FIVE_IN_A_ROW = 100000,
            OPPONENT_ONE_IN_A_ROW = 9,
            OPPONENT_TWO_IN_A_ROW = 99,
            OPPONENT_THREE_IN_A_ROW = 999,
            OPPONENT_FOUR_IN_A_ROW = 9999,
            OPPONENT_FIVE_IN_A_ROW = 99999
        };

        std::vector<std::vector<int>> _board;
        int _boardSize;

        std::pair<int, std::vector<int>> findPos(int depth, bool isPlayer);

        void evaluateBoard(std::vector<std::vector<int>> &scores, bool isPlayer);
        void evaluateDirection(std::vector<std::vector<int>> &scores, Direction direction, bool isPlayer);

        int evaluateScore(int pieces_count, bool isPlayer);

        void getOffset(Direction direction, int &x_offset, int &y_offset);
        void getStartEnd(Direction direction, int &x_start, int &y_start, int &x_end, int &y_end);
};

#endif /* !MOVEFINDER_HPP_ */
