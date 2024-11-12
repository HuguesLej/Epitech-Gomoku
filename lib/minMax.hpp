/*
** EPITECH PROJECT, 2024
** B-AIA-500-REN-5-1-gomoku-hugues.lejeune
** File description:
** minMax
*/

#ifndef MINMAX_HPP_
#define MINMAX_HPP_

struct Move {
    int row;
    int col;
};

struct GameState {
    int board[20][20];
};

// Fonction principale pour obtenir le meilleur coup
Move getBestMove(GameState currentState, int depth);

// Fonction pour vérifier si le coup est valide
bool isMoveValid(GameState currentState, int row, int col);

#endif /* !MINMAX_HPP_ */
