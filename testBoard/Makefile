SRC	=	src/main.cpp
BUILD_DIR = build
OBJ	=	$(SRC:src/%.cpp=$(BUILD_DIR)/%.o)

all:	$(OBJ)
	g++ -o testBoard $(OBJ)

$(BUILD_DIR)/%.o: src/%.cpp
	mkdir -p $(BUILD_DIR)
	g++ -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f testBoard

fclean:	clean
	rm -rf $(BUILD_DIR)

re:	fclean all