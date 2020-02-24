#pragma once
#include <SFML/Graphics.hpp>

class Cursor {
public:
	Cursor();

	void action();
	sf::Vector2i selected_cell();

	void set_cursor(sf::Vector2f _pos);
	sf::CircleShape &get_cursor();

	void draw(sf::RenderWindow  &_window);

	static const sf::Color select;
	static const sf::Color unselect;

private:
	sf::CircleShape cursor;
};