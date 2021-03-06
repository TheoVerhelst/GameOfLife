#include <algorithm>
#include <array>
#include <utility>
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
	const int gridHeight{static_cast<int>(grid.getHeight())},
		gridWidth{static_cast<int>(grid.getWidth())},
		intRow{static_cast<int>(row)},
		intCol{static_cast<int>(col)};
	const std::array<std::pair<int, int>, 8> neighboursToCheck{{
		{-1, -1}, {-1, 0}, {-1, 1},
		{ 0, -1},          { 0, 1},
		{ 1, -1}, { 1, 0}, { 1, 1}}};
	std::size_t res{0UL};
	for(auto& neighbour : neighboursToCheck)
	{
		int i{(intRow + neighbour.first) % gridHeight},
			j{(intCol + neighbour.second) % gridWidth};
		if(i < 0)
			i += gridHeight;
		if(j < 0)
			j += gridWidth;

		if(grid.getState(i, j) == State::Alive)
			++res;
	}
	return res;
}
