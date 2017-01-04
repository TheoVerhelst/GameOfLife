#include <cstdint>
#include <cmath>
#include <iostream>
#include "ThreadHelper.hpp"
#include "GameBoard.hpp"

using namespace std::placeholders;

GameBoard::GameBoard(const Grid& grid, sf::Vector2u size, bool useGradient,
	const std::map<State, sf::Color>& stateToColor, const State& stateNotToDraw):
	_grid{grid},
	_size{size},
	_squareSize{0u, 0u},
	_image{},
	_useGradient{useGradient},
	_gradientTime{0},
	_gradientSpeed{3.333},
	_stateToColor{stateToColor},
	_stateToGradientColor{_stateToColor},
	_stateNotToDraw{stateNotToDraw},
	_jobsCount{1}
{
	const std::size_t height{grid.getHeight()};
	const std::size_t width{grid.getWidth()};
	_squareSize.x = _size.x / width;
	_squareSize.y = _size.y / height;
	_image.create(_size.x, _size.y, _stateToGradientColor[_stateNotToDraw]);
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture, true);
	update(1);
}

void GameBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void GameBoard::update(std::size_t jobsCount)
{
	_jobsCount = jobsCount;
	_gradientTime += _gradientSpeed;

	if(_useGradient)
		for(auto& pair : _stateToColor)
			if(pair.first != _stateNotToDraw)
				_stateToGradientColor[pair.first] = computeGradient(pair.second, _gradientTime);

	_image.create(_size.x, _size.y, _stateToGradientColor[_stateNotToDraw]);
	ThreadHelper::dispatchWork(jobsCount,
		std::bind(&GameBoard::updateThreaded, this, _1, _2),
		_grid.getHeight() * _grid.getWidth());
	_texture.loadFromImage(_image);
}

void GameBoard::updateThreaded(std::size_t from, std::size_t to)
{
	const std::size_t fromLine{from / _grid.getWidth()}, toLine{((to - 1) / _grid.getWidth()) + 1};
	for(std::size_t i{fromLine}; i < toLine; ++i)
	{
		const std::size_t fromCol{i == fromLine ? from % _grid.getWidth() : 0};
		const std::size_t toCol{i == toLine - 1 ? ((to - 1) % _grid.getWidth() + 1) : _grid.getWidth()};
		for(std::size_t j{fromCol}; j < toCol; ++j)
		{
			const State state{_grid.getState(i, j)};
			if(state != _stateNotToDraw)
				for(std::size_t k{i * _squareSize.y}; k < (i + 1) * _squareSize.y; ++k)
					for(std::size_t l{j * _squareSize.x}; l < (j + 1) * _squareSize.x; ++l)
						_image.setPixel(l, k, _stateToGradientColor[state]);
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
