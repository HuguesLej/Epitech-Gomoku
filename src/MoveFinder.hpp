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
        std::vector<std::vector<int>> _board;
        int _boardSize;

        int findMoveScore(int x, int y);
        std::vector<int> findGreatestScore(std::vector<std::vector<int>> scores);
};

#endif /* !MOVEFINDER_HPP_ */
