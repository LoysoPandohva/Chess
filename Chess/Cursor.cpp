#include "Cursor.h"

Cursor::Cursor() {
	cursor.setRadius(15);
	cursor.setFillColor(unselect);
	cursor.setPosition(235, 235);
}

void Cursor::action() {
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
sf::Vector2i Cursor::selected_cell() {
	return sf::Vector2i(static_cast<int>(cursor.getPosition().x + 15) / 50 - 1,
		static_cast<int>(cursor.getPosition().y + 15) / 50 - 1);
}

void Cursor::set_cursor(sf::Vector2f _pos) {
	if ((_pos.x + 15.f) > 55 && (_pos.x + 15.f) < 445 && (_pos.y + 15.f) > 55 && (_pos.y + 15.f) < 445) {
		cursor.setPosition(_pos.x - 15, _pos.y - 15);
	}
	else if ((_pos.x + 15.f) > 55 && (_pos.x + 15.f) < 445 && (_pos.y + 15.f) < 55 && (_pos.y + 15.f) < 445) {
		cursor.setPosition(_pos.x - 15, 55 - 15);
	}
	else if ((_pos.x + 15.f) > 55 && (_pos.x + 15.f) < 445 && (_pos.y + 15.f) > 55 && (_pos.y + 15.f) > 445) {
		cursor.setPosition(_pos.x - 15, 445 - 15);
	}
	else if ((_pos.x + 15.f) < 55 && (_pos.x + 15.f) < 445 && (_pos.y + 15.f) > 55 && (_pos.y + 15.f) < 445) {
		cursor.setPosition(55 - 15, _pos.y - 15);
	}
	else if ((_pos.x + 15.f) > 55 && (_pos.x + 15.f) > 445 && (_pos.y + 15.f) > 55 && (_pos.y + 15.f) < 445) {
		cursor.setPosition(445 - 15, _pos.y - 15);
	}
}
sf::CircleShape& Cursor::get_cursor() {
	return cursor;
}

void Cursor::draw(sf::RenderWindow  &_window) {
	_window.draw(cursor);
}

const sf::Color Cursor::select = sf::Color(0, 80, 0, 60);
const sf::Color Cursor::unselect = sf::Color(80, 0, 0, 60);