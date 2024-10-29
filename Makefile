
SRC	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)

all:	$(OBJ)
	g++ -o pbrain-gomoku-ai $(OBJ)
	cp pbrain-gomoku-ai ../pbrain-player1.exe
	cp pbrain-gomoku-ai ../pbrain-player2.exe

clean:
	rm -f $(OBJ)
	rm -f pbrain-gomoku-ai

fclean:	clean

re:	fclean all