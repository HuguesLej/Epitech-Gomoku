/*
** EPITECH PROJECT, 2024
** B-AIA-500-REN-5-1-gomoku-hugues.lejeune
** File description:
** main
*/

#include "gomokuAI.hpp"

//-------------------------------------------------//
//                     constructor                 //
//-------------------------------------------------//

GomokuAI::GomokuAI() : initialized(false) {}

//-------------------------------------------------//
//                        main                     //
//-------------------------------------------------//

void GomokuAI::processCommand(const std::string &command) {
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

bool GomokuAI::checkPatternInDirection(int row, int col, int dRow, int dCol) {
    for (const auto& pattern : patterns) {
        bool match = true;
        for (int i = 0; i < pattern.size(); ++i) {
            int newRow = row + i * dRow;
            int newCol = col + i * dCol;
            if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) {
                match = false;
                break;
            }
            if (pattern[i] == 1 && board[newRow][newCol] != 1) {
                match = false;
                break;
            } else if (pattern[i] == 0 && board[newRow][newCol] != 0) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
};

bool GomokuAI::immediateWin() {

    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (board[row][col] == 1) {
                if (checkPatternInDirection(row, col, 0, 1) ||
                    checkPatternInDirection(row, col, 1, 0) ||
                    checkPatternInDirection(row, col, 1, 1) ||
                    checkPatternInDirection(row, col, 1, -1)) {
                    return true;
                }
            }
        }
    }
    return false;
};

void GomokuAI::makeMove() {

    // try {
    //     vec2 = checkRow();
    //     play_move(vec2[0], vec2[1]);
    //     return;
    // } catch (std::runtime_error &e) {
    //     (void) e;
    // }
    // try {
    //     vec2 = checkCol();
    //     play_move(vec2[0], vec2[1]);
    //     return;
    // } catch (std::runtime_error &e) {
    //     (void) e;
    // }
    // try {
    //     vec2 = checkDiagonals();
    //     play_move(vec2[0], vec2[1]);
    //     return;
    // } catch (std::runtime_error &e) {
    //     (void) e;
    // }

    MoveFinder finder(this->board, this->boardSize);

    vec2 = finder.findBestMove();
    play_move(vec2[0], vec2[1]);
}

//-------------------------------------------------//
//                     handlers                    //
//-------------------------------------------------//


void GomokuAI::handleStart(std::istringstream &stream) {
    stream >> boardSize;
    if (boardSize < 5 || boardSize > 20) {
        std::cout << "ERROR unsupported board size\n";
    } else {
        board = std::vector<std::vector<int>>(boardSize, std::vector<int>(boardSize, 0));
        initialized = true;
        std::cout << "OK\n";
    }
}

void GomokuAI::handleBegin() {
    if (!initialized)
        throw std::runtime_error("Game not initialized");
    play_move(10, 10);
}


void GomokuAI::handleTurn(std::istringstream &stream) {
    if (!initialized)
        throw std::runtime_error("Game not initialized");

    int x, y;
    char comma;
    stream >> x >> comma >> y;

    board[x][y] = 2; // Opponent move
    makeMove(); // AI move
}

void GomokuAI::handleBoard() {
    if (!initialized)
        throw std::runtime_error("Game not initialized");

    std::string line;
    int x, y, player;
    char comma;

    while (std::getline(std::cin, line) && line != "DONE") {
        std::istringstream lineStream(line);
        lineStream >> x >> comma >> y >> comma >> player;

        board[x][y] = player;
    }
    makeMove();
}

void GomokuAI::handleEnd() {
    print_board();
    std::cout << "Game over. Exiting.\n";
    std::exit(0);
}

void GomokuAI::print_board() {
    for (auto &j : board) {
        for (int i : j) {
            std::cout << i;
        }
        std::cout << std::endl;
    }
}

void GomokuAI::handleAbout() {
    std::cout << "name=\"GomokuAI\", version=\"1.0\", author=\"RandomAI\", country=\"France\"\n";
}


//-------------------------------------------------//
//                     helpers                     //
//-------------------------------------------------//


void GomokuAI::registerMoveOnBoard(int x, int y, int player) {
    board[x][y] = player;
}

int GomokuAI::play_move(int x, int y) {
    if (x == -1 && y == -1 || board[x][y] != 0)
        return 1;
        // throw std::runtime_error("Invalid move : " + std::to_string(x) + "," + std::to_string(y));
    registerMoveOnBoard(x, y, 1);
    std::cout << x << "," << y << "\n";
    return 0;
}

bool GomokuAI::checkLegalMove(int x, int y) {
    return x >= 0 && x < boardSize && y >= 0 && y < boardSize && board[x][y] == 0;
}
