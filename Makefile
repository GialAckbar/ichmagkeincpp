all: computerplayer.cpp gameboard.cpp gamemaster.cpp humanplayer.cpp main.cpp
	g++ computerplayer.cpp gameboard.cpp gamemaster.cpp humanplayer.cpp main.cpp -o tictactoe

clean:
	rm tictactoe