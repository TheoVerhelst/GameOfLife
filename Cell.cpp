#include <algorithm>
#include "Grid.hpp"
#include "Cell.hpp"

Cell::Cell(const State& state, const Grid& grid, std::size_t row, std::size_t col):
	_state{state},
	_grid{grid},
	_row{row},
	_col{col}
{
}

void Cell::update()
{
	std::size_t aliveNeighbours{countAliveNeighbours()};
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

std::size_t Cell::countAliveNeighbours() const
{
	std::size_t res{0},
				up{_row == 0 ? _row : _row - 1},
				down{_row == _grid.getHeight() - 1 ? _row : _row + 1},
				left{_col == 0 ? _col : _col - 1},
				right{_col == _grid.getWidth() - 1 ? _col : _col + 1};
	for(std::size_t i{up}; i <= down; ++i)
		for(std::size_t j{left}; j <= right; ++j)
			if(not (i == _row and j == _col) and _grid.getState(i, j) == State::Alive)
				res += 1;
	return res;
}
