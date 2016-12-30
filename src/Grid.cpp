#include <random>
#include <thread>
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

void Grid::update(std::size_t jobsCount)
{
	const Grid copy(*this);
	if(jobsCount > 1)
	{
		const std::size_t step{(getHeight() * getWidth()) / jobsCount};
		std::vector<std::thread> threads;

		for(std::size_t i{0}; i < jobsCount; ++i)
			threads.emplace_back(&Grid::updateThreaded, this, copy, i * step, (i + 1) * step);
		for(auto& thread : threads)
			thread.join();
	}
	else
		updateThreaded(copy, 0, getHeight() * getWidth());
}

void Grid::updateThreaded(const Grid& copy, std::size_t from, std::size_t to)
{
	const std::size_t fromLine{from / getWidth()}, toLine{((to - 1) / getWidth()) + 1};
	for(std::size_t i{fromLine}; i < toLine; ++i)
	{
		const std::size_t fromCol{i == fromLine ? from % getWidth() : 0};
		const std::size_t toCol{i == toLine - 1 ? ((to - 1) % getWidth() + 1) : _data[i].size()};
		for(std::size_t j{fromCol}; j < toCol; ++j)
			_data[i][j].update(copy, i, j);
	}
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
