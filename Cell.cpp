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
	std::size_t res{0},
				up{row == 0 ? row : row - 1},
				down{row == grid.getHeight() - 1 ? row : row + 1},
				left{col == 0 ? col : col - 1},
				right{col == grid.getWidth() - 1 ? col : col + 1};
	for(std::size_t i{up}; i <= down; ++i)
		for(std::size_t j{left}; j <= right; ++j)
			if(not (i == row and j == col) and grid.getState(i, j) == State::Alive)
				res += 1;
	return res;
}
