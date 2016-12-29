#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "GameBoard.hpp"

int main(int argc, char** argv)
{
	// Default parameters
	sf::Time updateTime{sf::seconds(0.1)};
	double aliveProbability{0.2};
	std::size_t height{70}, width{130};
	float cellSize{10.f};

	if(argc > 3)
		return 1;
	if(argc > 2)
		aliveProbability = std::stod(argv[2]);
	if(argc > 1)
		updateTime = sf::seconds(std::stod(argv[1]));

    sf::RenderWindow window(sf::VideoMode(cellSize * width, cellSize * height), "The Great Game of Life");

	Grid grid{height, width, aliveProbability};
	GameBoard gameBoard{grid, {cellSize * width, cellSize * height}};

	sf::Clock simulationClock;
	sf::Clock wholeSimulationClock;
	float simulationTicks{0.f};

    while(window.isOpen())
	{
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(simulationClock.getElapsedTime() >= updateTime)
        {
			simulationClock.restart();
			grid.update();
			gameBoard.update();
		}

        window.clear();
		simulationTicks += 1.f;
        window.draw(gameBoard);
        window.display();
    }
	std::cout << "In average " << (simulationTicks / wholeSimulationClock.getElapsedTime().asSeconds()) << " frame/s" << std::endl;
}
