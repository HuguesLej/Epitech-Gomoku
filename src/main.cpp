/*
** EPITECH PROJECT, 2024
** B-AIA-500-REN-5-1-gomoku-hugues.lejeune
** File description:
** main
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

class GomokuAI {
public:
    GomokuAI() : boardSize(20), initialized(false) {
        std::srand(static_cast<unsigned>(std::time(0))); // Seed for random moves
        for (int i = 0; i <= 20; i++)
            for (int j = 0; j <= 20; j++)
                board[i][j] = 0;
    }

    void processCommand(const std::string &command) {
        std::istringstream stream(command);
        std::string cmd;
        stream >> cmd;

        if (cmd == "START") {
            handleStart(stream);
        } else if (cmd == "BEGIN") {
            handleBegin();
        } else if (cmd == "TURN") {
            handleTurn(stream);
        } else if (cmd == "BOARD") {
            handleBoard();
        } else if (cmd == "END") {
            handleEnd();
        } else if (cmd == "ABOUT") {
            handleAbout();
        }
    }

private:
    int boardSize;
    bool initialized;
    int board[20][20];

    void handleStart(std::istringstream &stream) {
        stream >> boardSize;
        if (boardSize < 5 || boardSize > 20) {
            std::cout << "ERROR unsupported board size\n";
        } else {
            initialized = true;
            std::cout << "OK\n";
        }
    }

    void handleBegin() {
        if (!initialized) return;
        play_move(10, 10);
    }

    void handleTurn(std::istringstream &stream) {
        if (!initialized) return;

        int x, y;
        char comma;
        stream >> x >> comma >> y;

        board[x][y] = 2; // Opponent move
        makeRandomMove(); // AI move
    }

    void handleBoard() {
        if (!initialized) return;

        std::string line;
        int x, y, player;
        char comma;

        while (std::getline(std::cin, line) && line != "DONE") {
            std::istringstream lineStream(line);
            lineStream >> x >> comma >> y >> comma >> player;

            board[x][y] = player;
        }
        makeRandomMove();
    }

    void handleEnd() {
        print_board();
        std::cout << "Game over. Exiting.\n";
        std::exit(0);
    }

    void print_board() {
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                std::cout << board[i][j];
            }
            std::cout << "\n";
        }
    }

    void handleAbout() {
        std::cout << "name=\"GomokuAI\", version=\"1.0\", author=\"RandomAI\", country=\"France\"\n";
    }

    void makeRandomMove() {
        int x = -1;
        int y = -1;
        while (play_move(x, y) != 0) {
            x = std::rand() % boardSize;
            y = std::rand() % boardSize;
        }
    }

    int play_move(int x, int y) {
        if (x == -1 && y == -1 || board[x][y] != 0)
            return 1;
        board[x][y] = 1;
        std::cout << x << "," << y << "\n";
        return 0;
    }
};

int main() {
    GomokuAI ai;
    std::string command;

    while (std::getline(std::cin, command)) {
        ai.processCommand(command);
    }

    return 0;
}
