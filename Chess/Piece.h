#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Piece {
public: 
	Piece(bool _color, bool _first_move, int _x, int _y);

	virtual ~Piece() {};
	virtual void draw_piece(sf::RenderWindow &window) = 0;
	virtual void change_position(int _x, int _y) = 0;
	virtual void possible_move(Board &_board) = 0;
	
	sf::Vector2f coord_trans(sf::Vector2i _pos);

	sf::Vector2i &get_position();
	const bool &get_color();

	void make_first_move();
	bool get_first_move();

protected:
	sf::Vector2i position;
	bool color; // white - false, black - true
	bool first_move;
};