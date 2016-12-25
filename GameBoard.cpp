#include <cstdint>
#include "GameBoard.hpp"

GameBoard::GameBoard(const Grid& grid, sf::Vector2f size):
	_grid{grid},
	_size{size},
	_squares{},
	_stateToColor{{State::Alive, sf::Color(25, 25, 25)},
				  {State::Death, sf::Color(0, 0, 0)}}

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
	for(std::size_t i{0}; i < _squares.size(); ++i)
		for(std::size_t j{0}; j < _squares[i].size(); ++j)
			_squares[i][j].setFillColor(_stateToColor.at(_grid.getState(i, j)));
}
