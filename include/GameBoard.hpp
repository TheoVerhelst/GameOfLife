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
		GameBoard(const Grid& grid, sf::Vector2f size, bool useGradient=false);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(std::size_t jobsCount);

	private:
		void drawThreaded(std::size_t from, std::size_t to, sf::RenderTarget& target, sf::RenderStates states) const;
		void updateThreaded(std::size_t from, std::size_t to);
		static sf::Color computeGradient(const sf::Color& baseColor, double time);

		const Grid& _grid;
		sf::Vector2f _size;
		std::vector<std::vector<sf::RectangleShape>> _squares;
		const std::map<State, sf::Color> _stateToColor;
		bool _useGradient;
		double _gradientTime;
		double _gradientSpeed;
		std::size_t _jobsCount;
};

#endif // GAME_BOARD_HPP
