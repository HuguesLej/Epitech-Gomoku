/*
** EPITECH PROJECT, 2024
** B-AIA-500-REN-5-1-gomoku-hugues.lejeune
** File description:
** main
*/

#include "gomokuAI.hpp"

int main() {
    GomokuAI ai;
    std::string command;

    while (std::getline(std::cin, command)) {
        ai.processCommand(command);
    }

    return 0;
}
