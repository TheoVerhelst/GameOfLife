#include <random>
#include "Grid.hpp"

Grid::Grid(std::size_t height, std::size_t width, double aliveProbability)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution d(aliveProbability);

	for(std::size_t i{0}; i < height; ++i)
	{
		_data.emplace_back();
		for(std::size_t j{0}; j < width; ++j)
		{
			// Choose randomly if the cell is death or alive
			State state{State::Death};
			if(d(gen))
				state = State::Alive;

			_data.back().emplace_back(state, *this, i, j);
		}
	}
}

const State& Grid::getState(std::size_t row, std::size_t col) const
{
	return _data[row][col].getState();
}

void Grid::update()
{
	for(auto& line : _data)
		for(auto& cell : line)
			cell.update();
}

std::size_t Grid::getHeight() const
{
	return _data.size();
}

std::size_t Grid::getWidth() const
{
	if(not _data.empty())
		return _data.front().size();
	else
		return 0;
}
