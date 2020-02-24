#include "Pawn.h"

Pawn::Pawn(bool _color, bool _first_move, int _x, int _y) : Piece(_color, _first_move, _x, _y) {
	texture.loadFromFile("images//pieces.png");
	sprite.setTexture(texture);
	if (color == false) sprite.setTextureRect(sf::IntRect(0, 1, 30, 48));
	else sprite.setTextureRect(sf::IntRect(150, 51, 30, 48));
	sprite.setPosition(coord_trans(position).x, coord_trans(position).y);
}

void Pawn::possible_move(Board &_board) {
	if (color == true) {
		if (_board.get_all_cells(position.x, position.y - 1).get_employment() == 0) {
			_board.get_all_cells(position.x, position.y - 1).on_backlight();
			if (first_move == false) {
				if (_board.get_all_cells(position.x, position.y - 2).get_employment() == 0) {
					_board.get_all_cells(position.x, position.y - 2).on_backlight();
				}
			}
		}
		if (_board.get_all_cells(position.x - 1, position.y - 1).get_employment() == 1) {
			if (_board.get_all_cells(position.x - 1, position.y - 1).get_piece_color() != color) {
				_board.get_all_cells(position.x - 1, position.y - 1).on_backlight();
			}
		}
		if (_board.get_all_cells(position.x + 1, position.y - 1).get_employment() == 1) {
			if (_board.get_all_cells(position.x + 1, position.y - 1).get_piece_color() != color) {
				_board.get_all_cells(position.x + 1, position.y - 1).on_backlight();
			}
		}
	}
	if (color == false) {
		if (_board.get_all_cells(position.x, position.y + 1).get_employment() == 0) {
			_board.get_all_cells(position.x, position.y + 1).on_backlight();
			if (first_move == false) {
				if (_board.get_all_cells(position.x, position.y + 2).get_employment() == 0) {
					_board.get_all_cells(position.x, position.y + 2).on_backlight();
				}
			}
		}
		if (_board.get_all_cells(position.x - 1, position.y + 1).get_employment() == 1) {
			if (_board.get_all_cells(position.x - 1, position.y + 1).get_piece_color() != color) {
				_board.get_all_cells(position.x - 1, position.y + 1).on_backlight();
			}
		}
		if (_board.get_all_cells(position.x + 1, position.y + 1).get_employment() == 1) {
			if (_board.get_all_cells(position.x + 1, position.y + 1).get_piece_color() != color) {
				_board.get_all_cells(position.x + 1, position.y + 1).on_backlight();
			}
		}
	}
}

void Pawn::change_position(int _x, int _y) {
	position.x = _x;
	position.y = _y;
	sprite.setPosition(coord_trans(position).x, coord_trans(position).y);
}

void Pawn::draw_piece(sf::RenderWindow &_window) {
	_window.draw(sprite);
}