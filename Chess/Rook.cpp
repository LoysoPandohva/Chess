#include "Rook.h"

Rook::Rook(bool _color, bool _first_move, int _x, int _y) : Piece(_color, _first_move, _x, _y)
{
	texture.loadFromFile("images//pieces.png");
	sprite.setTexture(texture);
	if (color == false) sprite.setTextureRect(sf::IntRect(30, 0, 30, 48));
	else sprite.setTextureRect(sf::IntRect(120, 50, 30, 48));
	sprite.setPosition(coord_trans(position).x, coord_trans(position).y);
}

void Rook::possible_move(Board &_board) {
	sf::Vector2i current_pos = position;
	//-------------------DOWN---------------------------------
	while (current_pos.y + 1 < 8) {
		if (_board.get_all_cells(current_pos.x, current_pos.y + 1).get_employment() == false) {
			_board.get_all_cells(current_pos.x, current_pos.y + 1).on_backlight();
			current_pos.y++;
		}
		else if (_board.get_all_cells(current_pos.x, current_pos.y + 1).get_piece_color() != color) {
			_board.get_all_cells(current_pos.x, current_pos.y + 1).on_backlight();
			break;
		}
		else break;
	}
	//-------------------UP-----------------------------------
	current_pos = position;
	while (current_pos.y - 1 >= 0) {
		if (_board.get_all_cells(current_pos.x, current_pos.y - 1).get_employment() == false) {
			_board.get_all_cells(current_pos.x, current_pos.y - 1).on_backlight();
			current_pos.y--;
		}
		else if (_board.get_all_cells(current_pos.x, current_pos.y - 1).get_piece_color() != color) {
			_board.get_all_cells(current_pos.x, current_pos.y - 1).on_backlight();
			break;
		}
		else break;
	}
	//-------------------Right----------------------------------
	current_pos = position;
	while (current_pos.x + 1 < 8) {
		if (_board.get_all_cells(current_pos.x + 1, current_pos.y).get_employment() == false) {
			_board.get_all_cells(current_pos.x + 1, current_pos.y).on_backlight();
			current_pos.x++;
		}
		else if (_board.get_all_cells(current_pos.x + 1, current_pos.y).get_piece_color() != color) {
			_board.get_all_cells(current_pos.x + 1, current_pos.y).on_backlight();
			break;
		}
		else break;
	}
	//--------------------LEFT---------------------------------
	current_pos = position;
	while (current_pos.x - 1 >= 0) {
		if (_board.get_all_cells(current_pos.x - 1, current_pos.y).get_employment() == false) {
			_board.get_all_cells(current_pos.x - 1, current_pos.y).on_backlight();
			current_pos.x--;
		}
		else if (_board.get_all_cells(current_pos.x - 1, current_pos.y).get_piece_color() != color) {
			_board.get_all_cells(current_pos.x - 1, current_pos.y).on_backlight();
			break;
		}
		else break;
	}
}

void Rook::change_position(int _x, int _y) {
	position.x = _x;
	position.y = _y;
	sprite.setPosition(coord_trans(position).x, coord_trans(position).y);
}

void Rook::draw_piece(sf::RenderWindow &_window) {
	_window.draw(sprite);
}