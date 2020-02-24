#pragma once
#include "Piece.h"

class Pawn: public Piece {
public:
	Pawn(bool _color, bool _first_move, int _x, int _y);

	void possible_move(Board &_board);

	void change_position(int _x, int _y);

	void draw_piece(sf::RenderWindow &_window);

private:
	sf::Texture texture;
	sf::Sprite sprite;
};