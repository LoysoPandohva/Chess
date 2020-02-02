#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Piece {
public:
	Piece(bool _color, int _x, int _y): first_move(false), color(_color), position(_x, _y) {}

	virtual void draw_piece(sf::RenderWindow &window) = 0;

	virtual void change_position(int _x, int _y) = 0;
	
	virtual void possible_move(Board &_board) = 0;
	
	virtual ~Piece() {};
	
	sf::Vector2f coord_trans(sf::Vector2i _pos) {
		return sf::Vector2f(static_cast<float>(10 + (_pos.x + 1) * 50), static_cast<float>(1 + (_pos.y + 1) * 50));
	}

	sf::Vector2i &get_position() {
		return position;
	}
	const bool &get_color() {
		return color;
	}

	void make_first_move() {
		first_move = true;
	}
protected:
	sf::Vector2i position;
	bool color; // white - false, black - true
	bool first_move;
};