all:main.cpp
	g++ main.cpp Grid.cpp Cell.cpp GameBoard.cpp -I/home/theo/cpp/lib/boost_1_62_0 -L/home/theo/cpp/lib/boost_1_62_0/stage/lib -lsfml-system -lsfml-window -lsfml-graphics -lboost_program_options -Ofast -Wall -Wextra -std=c++14
