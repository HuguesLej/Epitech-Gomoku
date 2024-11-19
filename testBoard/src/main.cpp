#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <sstream>

class Board {
    private:
        std::vector<std::vector<int>> board;
        std::vector<std::pair<int, int>> moveP1;
        std::vector<std::pair<int, int>> moveP2;

    public: 
        std::pair<int, int> expectedMove;
        int size;

        std::string readFile(std::string path)
        {
            std::ifstream file(path);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open file: " + path);
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }


        void parseFile(std::string path)
        {
            std::string content = readFile(path);
            std::istringstream iss(content);
            std::string line;

            std::getline(iss, line);
            if (line.find("size:") != 0) {
                throw std::runtime_error("Invalid file format: missing size");
            }
            size = std::stoi(line.substr(5));

            // Initialize board
            board.resize(size, std::vector<int>(size, 0));

            // Parse board
            std::getline(iss, line); // Skip "board:" line
            for (int i = 0; i < size; i++) {
                std::getline(iss, line);
                for (int j = 0; j < size; j++) {
                    if (line[j] == '1') {
                        moveP1.push_back(std::pair(i, j));
                        board[i][j] = 1;
                    } else if (line[j] == '2') {
                        moveP2.push_back(std::pair(i, j));
                        board[i][j] = 2;
                    } else {
                        board[i][j] = 0;
                    }
                }
            }

            // Parse expected move
            std::getline(iss, line); // Skip line with board coordinates
            std::getline(iss, line); // Skip "expectedMove:" line
            std::getline(iss, line);
            std::istringstream moveStream(line);
            moveStream >> expectedMove.first;
            moveStream.ignore(1);
            moveStream >> expectedMove.second;
        }

        void printBoard()
        {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    std::cout << board[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

        std::string getBoardCommand()
        {
            std::string boardString = "BOARD\n";
            
            while (true) {
                if (moveP1.empty() || moveP2.empty()) {
                    break;
                }
                std::pair<int, int> move1 = moveP1.front();
                std::pair<int, int> move2 = moveP2.front();

                moveP1.erase(moveP1.begin());
                moveP2.erase(moveP2.begin());

                boardString += std::to_string(move1.first) + "," + std::to_string(move1.second) + ",1\n";
                boardString += std::to_string(move2.first) + "," + std::to_string(move2.second) + ",2\n";
            }

            boardString += "DONE\n";
            return boardString;
        }
};

bool debug = false;

bool handleOutput(char* buffer, ssize_t bytesRead, int aiOutput, std::pair<int, int> expectedMove) {
    if (bytesRead == -1) {
        throw std::runtime_error("Failed to read from AI's stdout");
    }
    buffer[bytesRead] = '\0';
    std::string output(buffer);
    std::istringstream iss(output);
    int x, y;
    char comma;
    iss >> x >> comma >> y;

    if (debug) std::cout << "Got : " << x << ", " << y << std::endl;
    return (x == expectedMove.first && y == expectedMove.second);
}


void openConnection(int toAIRead, int toAIWrite, int fromAIRead, int fromAIWrite) {
    dup2(toAIRead, STDIN_FILENO);
    dup2(fromAIWrite, STDOUT_FILENO);

    close(toAIRead);
    close(toAIWrite);
    close(fromAIRead);
    close(fromAIWrite);
}

bool testIa(int aiInput, int aiOutput, std::string file) {
    Board board;

    board.parseFile("boards/" + file);
    std::string boardCommand = board.getBoardCommand();
    if (debug) {
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "TESTING FILE: " << file << std::endl;
        std::cout << boardCommand <<  std::endl;
        // std::cout << "Size: " << board.size << std::endl;
        // board.printBoard();
        std::cout << "Expected move: " << board.expectedMove.first << "," << board.expectedMove.second << std::endl;
    }

    std::string input = "START 20\n";
    write(aiInput, input.c_str(), input.size());

    char buffer[128];
    ssize_t bytesRead = read(aiOutput, buffer, sizeof(buffer) - 1);

    if (bytesRead == -1) {
        throw std::runtime_error("Failed to read from AI's stdout");
    } else if (bytesRead == 0) {
        throw std::runtime_error("AI's stdout has been closed");
    } else {
        buffer[bytesRead] = '\0';
        std::string output(buffer);
        if (output.find("OK") != std::string::npos) {
            write(aiInput, boardCommand.c_str(), boardCommand.size());
        }
    }

    bytesRead = read(aiOutput, buffer, sizeof(buffer) - 1);
    bool passed = handleOutput(buffer, bytesRead, aiOutput, board.expectedMove);
    if (debug) std::cout << "-----------------------------------------" << std::endl;

    return passed;
}


int launchTest(std::string path, std::string file) {

    int toAI[2];    // Pipe to send data to AI's stdin
    int fromAI[2];  // Pipe to receive data from AI's stdout

    if (pipe(toAI) == -1 || pipe(fromAI) == -1) {
        std::cerr << "Pipe failed" << std::endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Fork failed" << std::endl;
        return 1;
    }

    if (pid == 0) {  // Child process (AI program)
        openConnection(toAI[0], toAI[1], fromAI[0], fromAI[1]);

        execlp(("./" + path).c_str(), nullptr);
        std::cerr << "Failed to start AI program" << std::endl;
        return 1;
    } else {
        close(toAI[0]);
        close(fromAI[1]);
        bool passed;

        try {
            passed = testIa(toAI[1], fromAI[0], file);
        } catch (std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }

        // Close pipes
        close(toAI[1]);
        close(fromAI[0]);

        // Wait for AI program to finish
        waitpid(pid, nullptr, 0);
        return passed ? 0 : 1;
    }

    return 0;
}


std::vector<std::string> scanFolder(std::string path)
{
    DIR* dir;
    struct dirent* ent;
    u_int32_t count = 0;
    std::vector<std::string> testFiles;

    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            if (ent->d_type == DT_REG) {
                std::string fileName = ent->d_name;
                std::cout << "Found test file : " << fileName << std::endl;
                testFiles.push_back(fileName);
                count++;
            }
        }
        if (count == 0) {
            throw std::runtime_error("No test files found in the directory");
        }
        closedir(dir);
    } else {
        throw std::runtime_error("Could not open directory: " + path);
    }
    return testFiles;
}

int main(int argc, char* argv[]) {
    std::string path = "";

    if (argc < 2) {
        std::cout << "Please provide the path to the AI program: ";
        std::cin >> path;
    } else {
        path = argv[1];
        if (argc == 3 && strcmp(argv[2], "-h") == 0) {
            std::cout << "Usage: ./main <path_to_ai_program> [-h]" << std::endl;
            return 0;
        } else if (argc == 3 && strcmp(argv[2], "-d") == 0) {
            debug = true;
        } else if (argc > 3) {
            std::cerr << "Invalid number of arguments" << std::endl;
            std::cout << "Usage: ./main <path_to_ai_program> [-h]" << std::endl;
            return 84;
        }
    }

    if (access(path.c_str(), F_OK) == -1) {
        std::cerr << "Cannot access the specified path" << std::endl;
        return 84;
    }

    std::vector<std::string> testFiles;
    
    try {
        testFiles = scanFolder("boards");
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    for (std::string file : testFiles) {
        if (launchTest(path, file) != 0) {
            std::cerr << "\033[1;31mTest '" << file << "' Failed\033[0m" << std::endl;
        } else {
            std::cout << "\033[1;32mTest '" << file << "' Passed\033[0m" << std::endl;
        }
    }
    return 0;
}
