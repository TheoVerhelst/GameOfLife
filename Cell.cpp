#include <algorithm>
#include "Grid.hpp"
#include "Cell.hpp"

Cell::Cell(const State& state):
	_state{state}
{
}

void Cell::update(const Grid& grid, std::size_t row, std::size_t col)
{
	const std::size_t aliveNeighbours{countAliveNeighbours(grid, row, col)};
	if(_state == State::Alive)
	{
		if(not (aliveNeighbours == 2 or aliveNeighbours == 3))
			_state = State::Death;
	}
	else
	{
		if(aliveNeighbours == 3)
			_state = State::Alive;
	}
}

const State& Cell::getState() const
{
	return _state;
}

std::size_t Cell::countAliveNeighbours(const Grid& grid, std::size_t row, std::size_t col) const
{
	int gridHeight{static_cast<int>(grid.getHeight())}, gridWidth{static_cast<int>(grid.getWidth())};
	std::size_t res{0};
	for(int i{-1}; i <= 1; ++i)
		for(int j{-1}; j <= 1; ++j)
			if(not (i == 0 and j == 0) and grid.getState((row + i)  % gridHeight, (col + j) % gridWidth) == State::Alive)
				res += 1;
	return res;
}
