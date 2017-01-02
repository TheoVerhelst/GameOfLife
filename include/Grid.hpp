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
		inline const State& getState(std::size_t row, std::size_t col) const;
		void update(std::size_t jobsCount);
		inline std::size_t getHeight() const;
		inline std::size_t getWidth() const;

	private:
		void updateThreaded(std::size_t from, std::size_t to, const Grid& copy);

		std::vector<std::vector<Cell>> _data;
};

const State& Grid::getState(std::size_t row, std::size_t col) const
{
	return _data[row][col].getState();
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

#endif // GRID_HPP
