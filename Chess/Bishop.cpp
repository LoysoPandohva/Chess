#include "Bishop.h"

Bishop::Bishop(bool _color, bool _first_move, int _x, int _y) : Piece(_color, _first_move, _x, _y)
{
	texture.loadFromFile("images//pieces.png");
	sprite.setTexture(texture);
	if (color == false) sprite.setTextureRect(sf::IntRect(90, 0, 30, 48));
	else sprite.setTextureRect(sf::IntRect(60, 50, 30, 48));
	sprite.setPosition(coord_trans(position).x, coord_trans(position).y);
}

void Bishop::possible_move(Board &_board) {
	sf::Vector2i current_pos = position;
	//-------------------DOWN-RIGHT------------------------
	while (current_pos.y + 1 < 8 && current_pos.x + 1 < 8) {
		if (_board.get_all_cells(current_pos.x + 1, current_pos.y + 1).get_employment() == false) {
			_board.get_all_cells(current_pos.x + 1, current_pos.y + 1).on_backlight();
			current_pos.x++;
			current_pos.y++;
		}
		else if (_board.get_all_cells(current_pos.x + 1, current_pos.y + 1).get_piece_color() != color) {
			_board.get_all_cells(current_pos.x + 1, current_pos.y + 1).on_backlight();
			break;
		}
		else break;
	}
	//-------------------UP-RIGHT-------------------------
	current_pos = position;
	while (current_pos.y - 1 >= 0 && current_pos.x + 1 < 8) {
		if (_board.get_all_cells(current_pos.x + 1, current_pos.y - 1).get_employment() == false) {
			_board.get_all_cells(current_pos.x + 1, current_pos.y - 1).on_backlight();
			current_pos.x++;
			current_pos.y--;
		}
		else if (_board.get_all_cells(current_pos.x + 1, current_pos.y - 1).get_piece_color() != color) {
			_board.get_all_cells(current_pos.x + 1, current_pos.y - 1).on_backlight();
			break;
		}
		else break;
	}
	//-------------------DOWN-LEFT-------------------------
	current_pos = position;
	while (current_pos.y + 1 < 8 && current_pos.x - 1 >= 0) {
		if (_board.get_all_cells(current_pos.x - 1, current_pos.y + 1).get_employment() == false) {
			_board.get_all_cells(current_pos.x - 1, current_pos.y + 1).on_backlight();
			current_pos.x--;
			current_pos.y++;
		}
		else if (_board.get_all_cells(current_pos.x - 1, current_pos.y + 1).get_piece_color() != color) {
			_board.get_all_cells(current_pos.x - 1, current_pos.y + 1).on_backlight();
			break;
		}
		else break;
	}
	//--------------------UP-LEFT------------------------
	current_pos = position;
	while (current_pos.y - 1 >= 0 && current_pos.x - 1 >= 0) {
		if (_board.get_all_cells(current_pos.x - 1, current_pos.y - 1).get_employment() == false) {
			_board.get_all_cells(current_pos.x - 1, current_pos.y - 1).on_backlight();
			current_pos.x--;
			current_pos.y--;
		}
		else if (_board.get_all_cells(current_pos.x - 1, current_pos.y - 1).get_piece_color() != color) {
			_board.get_all_cells(current_pos.x - 1, current_pos.y - 1).on_backlight();
			break;
		}
		else break;
	}
}
void Bishop::change_position(int _x, int _y) {
	position.x = _x;
	position.y = _y;
	sprite.setPosition(coord_trans(position).x, coord_trans(position).y);
}
void Bishop::draw_piece(sf::RenderWindow &_window) {
	_window.draw(sprite);
}