#pragma once
#include <SFML/Graphics.hpp>

class Cursor {
public:
	Cursor() {
		cursor.setRadius(15);
		cursor.setFillColor(unselect);
		cursor.setPosition(235, 235);
	}
	void action() {
		float speed = 4;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { speed = 8; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			cursor.move(0, -speed);
			if (cursor.getPosition().y + 15 < 55) {
				cursor.move(0, speed);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			cursor.move(speed, 0);
			if (cursor.getPosition().x + 15 > 445) {
				cursor.move(-speed, 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			cursor.move(0, speed);
			if (cursor.getPosition().y + 15 > 445) {
				cursor.move(0, -speed);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			cursor.move(-speed, 0);
			if (cursor.getPosition().x + 15 < 55) {
				cursor.move(speed, 0);
			}
		}
	}

	sf::Vector2i selected_cell() {
		return sf::Vector2i(static_cast<int>(cursor.getPosition().x + 15) / 50 - 1,
			static_cast<int>(cursor.getPosition().y + 15) / 50 - 1);
	}

	sf::CircleShape &get_cursor() {
		return cursor;
	}
	void draw(sf::RenderWindow  &_window) {
		_window.draw(cursor);
	}
	
	static const sf::Color select;
	static const sf::Color unselect;

private:
	sf::CircleShape cursor;
};