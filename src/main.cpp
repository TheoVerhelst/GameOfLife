#include <iostream>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "GameBoard.hpp"


namespace program_options = boost::program_options;

int main(int argc, char** argv)
{
	// Default parameters
	float updateTimeDouble;
	double aliveProbability;
	std::size_t height{50}, width{50};
	float cellSize{10.f};

	// Declare the supported options.
	program_options::options_description options("Allowed options");
	options.add_options()
		("help,h", "show this help and exit")
		("alive-probability,p", program_options::value<double>(&aliveProbability)->default_value(.4),
			"set probability that initial cell is alive")
		("update-time,t", program_options::value<float>(&updateTimeDouble)->default_value(.1f),
			"minimum time between two updates");

	program_options::variables_map variablesMap;
	program_options::store(program_options::parse_command_line(argc, argv, options), variablesMap);
	program_options::notify(variablesMap);

	if(variablesMap.count("help"))
	{
		std::cout << options << std::endl;
		return 0;
	}

	sf::Time updateTime{sf::seconds(updateTimeDouble)};
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
