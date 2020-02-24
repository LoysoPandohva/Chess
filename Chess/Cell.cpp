#include "Cell.h"

const sf::Color Cell::black = sf::Color(80, 80, 80);
const sf::Color Cell::white = sf::Color(222, 222, 222);
const sf::Color Cell::green = sf::Color(0, 100, 0, 80);

Cell::Cell() : backlight(false), employment(false), piece_color(false) {
	square.setSize(sf::Vector2f(50.f, 50.f));
	square.setOutlineThickness(2);
	square.setOutlineColor(sf::Color(0, 0, 0));
}

sf::RectangleShape& Cell::get_cell() {
	return square;
}
void Cell::set_position(float _x, float _y) {
	square.setPosition(_x, _y);
}
void Cell::set_color(sf::Color _new_color) {
	square.setFillColor(_new_color);
}

void Cell::on_backlight() {
	backlight = true;
	actuality_color = green;
}
void Cell::off_backlight() {
	backlight = false;
}
bool Cell::get_backlight() {
	return backlight;
}

void Cell::employment_cell(bool _color) {
	employment = true;
	piece_color = _color;
}
void Cell::free_cell() {
	employment = false;
}
bool Cell::get_employment() {
	return employment;
}
bool Cell::get_piece_color() {
	return piece_color;
}