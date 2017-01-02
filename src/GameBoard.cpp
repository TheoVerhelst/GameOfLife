#include <cstdint>
#include <cmath>
#include <iostream>
#include "ThreadHelper.hpp"
#include "GameBoard.hpp"

using namespace std::placeholders;

GameBoard::GameBoard(const Grid& grid, sf::Vector2f size, bool useGradient):
	_grid{grid},
	_size{size},
	_squares{},
	_stateToColor{{State::Alive, sf::Color(255, 255, 255)},
				  {State::Death, sf::Color(0, 0, 0)}},
	_useGradient{useGradient},
	_gradientTime{0},
	_gradientSpeed{3.333},
	_jobsCount{1}
{
	std::size_t height{grid.getHeight()};
	std::size_t width{grid.getWidth()};
	sf::Vector2f squareSize{_size.x / static_cast<float>(width), _size.y / static_cast<float>(height)};

	for(std::size_t i{0}; i < height; ++i)
	{
		_squares.emplace_back();
		for(std::size_t j{0}; j < width; ++j)
		{
			sf::RectangleShape square(squareSize);
			square.setPosition(squareSize.x * static_cast<float>(j), squareSize.y * static_cast<float>(i));
			_squares.back().push_back(square);
		}
	}
	update(1);
}

void GameBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(std::size_t i{0}; i < _squares.size(); ++i)
		for(std::size_t j{0}; j < _squares[i].size(); ++j)
			if(_grid.getState(i, j) != State::Death)
				target.draw(_squares[i][j], states);
}

void GameBoard::update(std::size_t jobsCount)
{
	_jobsCount = jobsCount;
	_gradientTime += _gradientSpeed;
	ThreadHelper::dispatchWork(jobsCount,
		std::bind(&GameBoard::updateThreaded, this, _1, _2),
		_grid.getHeight() * _grid.getWidth());
}

void GameBoard::updateThreaded(std::size_t from, std::size_t to)
{
	const std::size_t fromLine{from / _grid.getWidth()}, toLine{((to - 1) / _grid.getWidth()) + 1};
	for(std::size_t i{fromLine}; i < toLine; ++i)
	{
		const std::size_t fromCol{i == fromLine ? from % _grid.getWidth() : 0};
		const std::size_t toCol{i == toLine - 1 ? ((to - 1) % _grid.getWidth() + 1) : _squares[i].size()};
		for(std::size_t j{fromCol}; j < toCol; ++j)
		{
			sf::Color squareColor{_stateToColor.at(_grid.getState(i, j))};
			if(_useGradient)
				squareColor = computeGradient(squareColor, _gradientTime);
			_squares[i][j].setFillColor(squareColor);
		}
	}
}

sf::Color GameBoard::computeGradient(const sf::Color& baseColor, double time)
{
	sf::Color gradientColor;
	time += static_cast<double>(baseColor.toInteger());
	sf::Uint8 remainder = static_cast<sf::Uint8>(fmod(time, 256.));
	time = fmod(time, 6. * 256.);

	if(time < 1. * 256.)
		gradientColor = sf::Color(255, remainder, 0);
	else if(time < 2. * 256.)
		gradientColor = sf::Color(255 - remainder, 255, 0);
	else if(time < 3. * 256.)
		gradientColor = sf::Color(0, 255, remainder);
	else if(time < 4. * 256.)
		gradientColor = sf::Color(0, 255 - remainder, 255);
	else if(time < 5. * 256.)
		gradientColor = sf::Color(remainder, 0, 255);
	else
		gradientColor = sf::Color(255, 0, 255 - remainder);
	return gradientColor;
}
