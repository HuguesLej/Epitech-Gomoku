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

GomokuAI::GomokuAI() : initialized(false) {
    std::srand(static_cast<unsigned>(std::time(0))); // Seed for random moves
}


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

std::vector<int> GomokuAI::checkRow()
{
    std::vector<int> vec = {0, 0};
    int count = 0;

    for (auto col : board) {
        for (auto row : col) {
            if (col[row] == 1) {
                count++;
            } else {
                count = 0;
            }
            if (count == 4) {
                vec[0] = row;
                vec[1] = &col - &board[0] + 1;
                if (checkLegalMove(vec[0], vec[1])) { return vec; }
                vec[1] = &col - &board[0] - 5;
                if (checkLegalMove(vec[0], vec[1])) { return vec; }
            }
        }
    }
    throw std::runtime_error("No win move found");
}

std::vector<int> GomokuAI::checkCol()
{
    std::vector<int> vec = {0, 0};
    int count = 0;

    for (auto col : board) {
        for (auto row : col) {
            if (col[row] == 1) {
                count++;
            } else {
                count = 0;
            }
            if (count == 4) {
                vec[0] = row + 1;
                vec[1] = &col - &board[0];
                if (checkLegalMove(vec[0], vec[1])) { return vec; }
                vec[0] = row - 5;
                if (checkLegalMove(vec[0], vec[1])) { return vec; }
            }
        }
    }
    throw std::runtime_error("No win move found");
}

std::vector<int> GomokuAI::checkDiagonals()
{
    std::vector vec2 = {0, 0};

    for (int i = 0; i < boardSize - 4; ++i) {
        for (int j = 0; j < boardSize - 4; ++j) {
            int count = 0;
            for (int k = 0; k < 5; ++k) {
                if (board[i + k][j + k] == 1) {
                    count++;
                } else {
                    count = 0;
                    break;
                }
                if (count == 4) {
                    vec2[0] = i + k + 1;
                    vec2[1] = j + k + 1;
                    if (checkLegalMove(vec2[0], vec2[1])) { return vec2; }
                    vec2[0] = i + k - 4;
                    vec2[1] = j + k - 4;
                    if (checkLegalMove(vec2[0], vec2[1])) { return vec2; }
                }
            }
        }
    }

    for (int i = 4; i < boardSize; ++i) {
        for (int j = 0; j < boardSize - 4; ++j) {
            int count = 0;
            for (int k = 0; k < 5; ++k) {
                if (board[i - k][j + k] == 1) {
                    count++;
                } else {
                    count = 0;
                    break;
                }
                if (count == 4) {
                    vec2[0] = i - k - 1;
                    vec2[1] = j + k + 1;
                    if (checkLegalMove(vec2[0], vec2[1])) { return vec2; }
                    vec2[0] = i - k + 4;
                    vec2[1] = j + k - 4;
                    if (checkLegalMove(vec2[0], vec2[1])) { return vec2; }
                }
            }
        }
    }
    throw std::runtime_error("No win move found");
}


void GomokuAI::makeMove() {
    std::vector vec2 = {0, 0};

    try {
        vec2 = checkRow();
        play_move(vec2[0], vec2[1]);
        return;
    } catch (std::runtime_error &e) {}
    try {
        vec2 = checkCol();
        play_move(vec2[0], vec2[1]);
        return;
    } catch (std::runtime_error &e) {}
    try {
        vec2 = checkDiagonals();
        play_move(vec2[0], vec2[1]);
        return;
    } catch (std::runtime_error &e) {}

    makeRandomMove();
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


void GomokuAI::makeRandomMove() {
    int x = -1;
    int y = -1;
    while (play_move(x, y) != 0) {
        x = std::rand() % boardSize;
        y = std::rand() % boardSize;
    }
}

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
