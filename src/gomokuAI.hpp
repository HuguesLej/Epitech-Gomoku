#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#ifndef GOMOKUAI_HPP
#define GOMOKUAI_HPP


class GomokuAI {
public:
    GomokuAI();
    ~GomokuAI() = default;

    /**
     * @brief Process a command from the standard input
     * @param command the command to process
     * @return void
     */
    void processCommand(const std::string &command);

private:
    int boardSize;
    bool initialized;
    std::vector <std::vector<int>> board;

    /**
     * @brief Handle the start of the game
     * @param stream the stream containing the board size
     * @return void
     */
    void handleStart(std::istringstream &stream);

    /**
     * @brief Handle the beginning of the game
     * @return void
     */
    void handleBegin();

    /**
     * @brief Handle the turn of the opponent
     * @param stream the stream containing the opponent move
     * @return void
     */
    void handleTurn(std::istringstream &stream);

    /**
     * @brief Handle the update of the board
     * @return void
     */
    void handleBoard();

    /**
     * @brief Handle the end of the game
     * @return void
     */
    void handleEnd();

    /**
     * @brief Print the name, version, author and country of the AI, with the following format:
     * name="", version="", author="", country=""
     * @return void
     */
    void handleAbout();

    /**
     * @brief Print the board on the standard output
     */
    void print_board();

    void makeRandomMove();

    /**
     * @brief Play a move on the board
     * @param x the x coordinate
     * @param y the y coordinate
     * @return print the move on the standard output
     * @throw std::runtime_error if the move is invalid
     */
    int play_move(int x, int y);

    /**
     * @brief Register a move on the board
     * @param x the x coordinate
     * @param y the y coordinate
     * @param player the player id
     * @return void
     */
    void registerMoveOnBoard(int x, int y, int player);
};


#endif //GOMOKUAI_HPP