all:main.cpp
	g++ main.cpp Grid.cpp Cell.cpp GameBoard.cpp -lsfml-system -lsfml-window -lsfml-graphics -Ofastm -Wall -Wextra -pg -std=c++14 -o gameOfLife
