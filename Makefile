all:main.cpp
	g++ main.cpp Grid.cpp Cell.cpp GameBoard.cpp -lsfml-system -lsfml-window -lsfml-graphics -g -std=c++14 -o gameOfLife
