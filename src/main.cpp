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
	// Parameters
	float updateTimeDouble;
	double aliveProbability;
	std::size_t height, width;
	float cellSize;
	std::size_t jobsCount;
	bool useGradient;

	// Declare the options
	program_options::options_description options("Allowed options");
	options.add_options()
		("help", "show this help and exit")
		("alive-probability,p", program_options::value<double>(&aliveProbability)->default_value(0.5),
			"proportion of alive cells at the first step")
		("update-time,t", program_options::value<float>(&updateTimeDouble)->default_value(0.25f),
			"minimum time between two steps")
		("jobs,j", program_options::value<std::size_t>(&jobsCount)->default_value(1),
			"number of parallel jobs to run")
		("width,w", program_options::value<std::size_t>(&width)->default_value(20),
			"width of the grid, in number of cases")
		("height,h", program_options::value<std::size_t>(&height)->default_value(20),
			"height of the grid, in number of cases")
		("gradient,g", boost::program_options::bool_switch(&useGradient),
			"use a fancy gradient feature")
		("cell-size,c", program_options::value<float>(&cellSize)->default_value(10.f),
			"size of a cell, in pixels")
	;

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
	GameBoard gameBoard{grid, {cellSize * width, cellSize * height}, useGradient};

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
			grid.update(jobsCount);
			gameBoard.update(jobsCount);
		}

        window.clear();
		simulationTicks += 1.f;
        window.draw(gameBoard);
        window.display();
    }
	std::cout << "In average " << (simulationTicks / wholeSimulationClock.getElapsedTime().asSeconds()) << " frame/s" << std::endl;
}
