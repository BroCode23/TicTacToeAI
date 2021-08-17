all: run

run: functions.o TicTacToeAI.o
	c++ -g -std=c++11 functions.o TicTacToeAI.o -o ticTacToe

functions.o: functions.cpp functions.h
	c++ -g -std=c++11 -c functions.cpp

TicTacToeAI.o: TicTacToeAI.cpp
	c++ -g -std=c++11 -c TicTacToeAI.cpp

clean:
	rm *.o TicTacToeAI
