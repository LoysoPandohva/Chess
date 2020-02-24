#include "Piece.h"

Piece::Piece(bool _color, bool _first_move, int _x, int _y) : color(_color), first_move(_first_move), position(_x, _y) {}

sf::Vector2f Piece::coord_trans(sf::Vector2i _pos) {
	return sf::Vector2f(static_cast<float>(10 + (_pos.x + 1) * 50), static_cast<float>(1 + (_pos.y + 1) * 50));
}

sf::Vector2i& Piece::get_position() {
	return position;
}
const bool& Piece::get_color() {
	return color;
}

void Piece::make_first_move() {
	first_move = true;
}
bool Piece::get_first_move() {
	return first_move;
}