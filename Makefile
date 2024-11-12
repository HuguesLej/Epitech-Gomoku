SRC	=	src/main.cpp
BUILD_DIR = build
OBJ	=	$(BUILD_DIR)/$(SRC:.cpp=.o)

all:	$(OBJ)
	g++ -o pbrain-gomoku-ai $(OBJ)
	mkdir -p bin
	cp pbrain-gomoku-ai bin/pbrain-player1.exe
	cp pbrain-gomoku-ai bin/pbrain-player2.exe

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(BUILD_DIR)
	g++ -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f pbrain-gomoku-ai

fclean:	clean
	rm -rf $(BUILD_DIR)
	rm -rf bin

re:	fclean all