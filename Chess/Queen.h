#pragma once
#include "Piece.h"

class Queen: public Piece {
public:
	Queen(bool _color, bool _first_move, int _x, int _y);

	void possible_move(Board &_board);

	void change_position(int _x, int _y) override;

	void draw_piece(sf::RenderWindow &_window) override;

private:
	sf::Texture texture;
	sf::Sprite sprite;
};