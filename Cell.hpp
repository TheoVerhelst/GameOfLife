#ifndef CELL_HPP
#define CELL_HPP

#include <cstdint>
#include "State.hpp"

class Grid;

class Cell
{
	public:
		Cell(const State& state, const Grid& grid, std::size_t row, std::size_t col);
		void update();
		const State& getState() const;

	private:
		std::size_t countAliveNeighbours() const;

		State _state;
		const Grid& _grid;
		std::size_t _row, _col;
};

#endif // CELL_HPP
