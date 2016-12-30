#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <cstdint>
#include "State.hpp"
#include "Cell.hpp"

class Grid
{
	public:
		Grid(std::size_t height, std::size_t width, double aliveProbability);
		const State& getState(std::size_t row, std::size_t col) const;
		void update(std::size_t jobsCount);
		std::size_t getHeight() const;
		std::size_t getWidth() const;

	private:
		void updateThreaded(const Grid& copy, std::size_t from, std::size_t to);

		std::vector<std::vector<Cell>> _data;
};

#endif // GRID_HPP
