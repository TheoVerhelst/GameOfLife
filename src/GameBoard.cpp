#include <cstdint>
#include <cmath>
#include "GameBoard.hpp"

GameBoard::GameBoard(const Grid& grid, sf::Vector2f size):
	_grid{grid},
	_size{size},
	_squares{},
	_stateToColor{{State::Alive, sf::Color(255, 255, 255)},
				  {State::Death, sf::Color(0, 0, 0)}},
	_gradient{true},
	_gradientTime{0},
	_gradientSpeed{3.333}
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
	update();
}

void GameBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for(auto& line : _squares)
		for(auto& square : line)
			target.draw(square, states);
}

void GameBoard::update()
{
	_gradientTime += _gradientSpeed;
	for(std::size_t i{0}; i < _squares.size(); ++i)
	{
		for(std::size_t j{0}; j < _squares[i].size(); ++j)
		{
			sf::Color squareColor{_stateToColor.at(_grid.getState(i, j))};
			if(_gradient)
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