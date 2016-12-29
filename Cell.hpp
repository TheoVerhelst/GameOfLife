#ifndef CELL_HPP
#define CELL_HPP

#include <cstdint>
#include "State.hpp"

class Grid;

class Cell
{
	public:
		Cell(const State& state);
		void update(const Grid& grid, std::size_t row, std::size_t col);
		const State& getState() const;

	private:
		std::size_t countAliveNeighbours(const Grid& grid, std::size_t row, std::size_t col) const;

		State _state;
};

#endif // CELL_HPP
