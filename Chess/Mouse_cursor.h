#pragma once
#include <SFML/Graphics.hpp>

class Mouse_cursor {
public:
	sf::Vector2i get_mause_pos(sf::RenderWindow &_window) {
		return sf::Mouse::getPosition(_window);
	}
};