all:main.cpp
	g++ main.cpp Grid.cpp Cell.cpp GameBoard.cpp -lsfml-system -lsfml-window -lsfml-graphics -Ofast -Wall -Wextra -pg -std=c++14
