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
		GameBoard(const Grid& grid, sf::Vector2f size);
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void update();

	private:
		static sf::Color computeGradient(const sf::Color& baseColor, double time);

		const Grid& _grid;
		sf::Vector2f _size;
		std::vector<std::vector<sf::RectangleShape>> _squares;
		const std::map<State, sf::Color> _stateToColor;
		bool _gradient;
		double _gradientTime;
		double _gradientSpeed;
};

#endif // GAME_BOARD_HPP
