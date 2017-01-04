#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "State.hpp"

class GameBoard : public sf::Drawable, sf::Transformable
{
	public:
		GameBoard(const Grid& grid, sf::Vector2u size, bool useGradient,
		const std::map<State, sf::Color>& stateToColor, const State& stateNotToDraw);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(std::size_t jobsCount);

	private:
		void updateThreaded(std::size_t from, std::size_t to);
		static sf::Color computeGradient(const sf::Color& baseColor, double time);

		const Grid& _grid;
		sf::Vector2u _size;
		sf::Vector2u _squareSize;
		sf::Image _image;
		sf::Texture _texture;
		sf::Sprite _sprite;
		bool _useGradient;
		double _gradientTime;
		double _gradientSpeed;
		const std::map<State, sf::Color>& _stateToColor;
		std::map<State, sf::Color> _stateToGradientColor;
		const State& _stateNotToDraw;
		std::size_t _jobsCount;
};

#endif // GAME_BOARD_HPP
