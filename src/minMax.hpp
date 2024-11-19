/*
** EPITECH PROJECT, 2024
** B-AIA-500-REN-5-1-gomoku-hugues.lejeune
** File description:
** minMax
*/

#ifndef MINMAX_HPP_
#define MINMAX_HPP_

#include <vector>
#include <climits>

class minMax {
private:
    int minimax(std::vector<std::vector<int>>& board, int depth, bool isMaximizing);
    int evaluate(std::vector<std::vector<int>>& board);
    bool canPlay(std::vector<std::vector<int>>& board);
    int calculateScore(int countPlayer, int countOpponent);
public:
    std::pair<int, int> findBestMove(std::vector<std::vector<int>>& board, int player);
};

#endif /* !MINMAX_HPP_ */
