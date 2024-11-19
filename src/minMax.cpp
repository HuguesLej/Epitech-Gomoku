/*
** EPITECH PROJECT, 2024
** B-AIA-500-REN-5-1-gomoku-hugues.lejeune
** File description:
** minMax
*/

#include "minMax.hpp"

std::pair<int, int> minMax::findBestMove(std::vector<std::vector<int>>& board, int player)
{
    std::pair<int, int> bestMove = {-1, -1};
    int bestScore = INT_MIN;

    for (auto i = 0; i < board.size(); i++) {
        for (auto j = 0; j < board.size(); j++) {
            if (board[i][j] == 0) {
                board[i][j] = player;
                int score = minimax(board, 0, false);
                board[i][j] = 0;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove.first = i;
                    bestMove.second = j;
                }
            }
        }
    }
    return bestMove;
}

int minMax::minimax(std::vector<std::vector<int>>& board, int depth, bool isMaximizing)
{
    int score = evaluate(board);
    if (depth == 0 || !canPlay(board) || score == 1000 || score == -1000) {
        return score;
    }
    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (auto i = 0; i < board.size(); i++) {
            for (auto j = 0; j < board.size(); j++) {
                if (board[i][j] == 0) {
                    board[i][j] = 1;
                    bestScore = std::max(bestScore, minimax(board, depth - 1, !isMaximizing));
                    board[i][j] = 0;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (auto i = 0; i < board.size(); i++) {
            for (auto j = 0; j < board.size(); j++) {
                if (board[i][j] == 0) {
                    board[i][j] = 2;
                    bestScore = std::min(bestScore, minimax(board, depth - 1, !isMaximizing));
                    board[i][j] = 0;
                }
            }
        }
        return bestScore;
    }
}

bool minMax::canPlay(std::vector<std::vector<int>>& board)
{
    for (auto i = 0; i < board.size(); i++) {
        for (auto j = 0; j < board.size(); j++) {
            if (board[i][j] == 0)
                return true;
        }
    }
    return false;
}

int minMax::evaluate(std::vector<std::vector<int>>& board) {
    int score = 0;

    // Rows
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            int countPlayer = 0, countOpponent = 0;
            for (int k = 0; k < 5; k++) {
                if (j + k >= board.size())
                    break;
                if (board[i][j + k] == 1)
                    countPlayer++;
                else if (board[i][j + k] == 2)
                    countOpponent++;
            }
            score += calculateScore(countPlayer, countOpponent);
        }
    }

    // Columns
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            int countPlayer = 0, countOpponent = 0;
            for (int k = 0; k < 5; k++) {
                if (i + k >= board.size())
                    break;
                if (board[i + k][j] == 1)
                    countPlayer++;
                else if (board[i + k][j] == 2)
                    countOpponent++;
            }
            score += calculateScore(countPlayer, countOpponent);
        }
    }

    // Diagonals right (top-left to bottom-right)
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            int countPlayer = 0, countOpponent = 0;
            for (int k = 0; k < 5; k++) {
                if (i + k >= board.size() || j + k >= board.size())
                    break;
                if (board[i + k][j + k] == 1)
                    countPlayer++;
                else if (board[i + k][j + k] == 2)
                    countOpponent++;
            }
            score += calculateScore(countPlayer, countOpponent);
        }
    }

    // Diagonals left (top-right to bottom-left)
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            int countPlayer = 0, countOpponent = 0;
            for (int k = 0; k < 5; k++) {
                if (i + k >= board.size() || j - k < 0)
                    break;
                if (board[i + k][j - k] == 1)
                    countPlayer++;
                else if (board[i + k][j - k] == 2)
                    countOpponent++;
            }
            score += calculateScore(countPlayer, countOpponent);
        }
    }

    return score;
}

int minMax::calculateScore(int countPlayer, int countOpponent) {
    if (countPlayer == 5) return 1000;  // AI wins
    if (countOpponent == 5) return -1000;  // Opponent wins
    if (countPlayer == 4 && countOpponent == 0) return 100;  // 4 in a row
    if (countPlayer == 3 && countOpponent == 0) return 10;  // 3 in a row
    if (countPlayer == 2 && countOpponent == 0) return 1;   // 2 in a row
    if (countOpponent == 4 && countPlayer == 0) return -100;  // Opponent has 4 in a row
    if (countOpponent == 3 && countPlayer == 0) return -10;   // Opponent has 3 in a row
    if (countOpponent == 2 && countPlayer == 0) return -1;    // Opponent has 2 in a row
    return 0;  // Nothing
}
