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
			// Choose randomly whether the cell is dead or alive
			State state{State::Death};
			if(d(gen))
				state = State::Alive;

			_data.back().emplace_back(state);
		}
	}
}

const State& Grid::getState(std::size_t row, std::size_t col) const
{
	return _data[row][col].getState();
}

void Grid::update()
{
	Grid copy(*this);
	for(std::size_t i{0}; i < _data.size(); ++i)
		for(std::size_t j{0}; j < _data[i].size(); ++j)
			_data[i][j].update(copy, i, j);
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
