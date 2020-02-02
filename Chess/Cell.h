#pragma once
#include <SFML/Graphics.hpp>

class Cell {
public:
	Cell();

	sf::RectangleShape& get_cell();
	void set_position(float _x, float _y);
	void set_color(sf::Color _new_color);

	void on_backlight();
	void off_backlight();
	bool get_backlight();

	void employment_cell(bool _color);
	void free_cell();
	bool get_employment();
	bool get_piece_color();

	static const sf::Color black;
	static const sf::Color white;
	static const sf::Color green;

private:
	bool backlight = false;
	bool employment = false;
	bool piece_color = false;
	sf::RectangleShape square;
	sf::Color actuality_color;
};