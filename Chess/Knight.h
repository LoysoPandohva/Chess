#pragma once
#include "Piece.h"

class Knight: public Piece {
public:
	Knight(bool _color, bool _first_move, int _x, int _y) : Piece(_color, _first_move, _x, _y)
	{
		texture.loadFromFile("images//pieces.png");
		sprite.setTexture(texture);
		if (color == false) sprite.setTextureRect(sf::IntRect(60, 0, 30, 48));
		else sprite.setTextureRect(sf::IntRect(90, 50, 30, 48));
		sprite.setPosition(coord_trans(position).x, coord_trans(position).y);
	}

	void possible_move(Board &_board) {
		sf::Vector2i current_pos = position;
		//-------------------DOWN-RIGHT------------------------
		if (current_pos.x + 1 < 8 && current_pos.y + 2 < 8) {
			if (_board.get_all_cells(current_pos.x + 1, current_pos.y + 2).get_employment() == false) {
				_board.get_all_cells(current_pos.x + 1, current_pos.y + 2).on_backlight();
			}
			else if (_board.get_all_cells(current_pos.x + 1, current_pos.y + 2).get_piece_color() != color) {
				_board.get_all_cells(current_pos.x + 1, current_pos.y + 2).on_backlight();
			}
		}
		//-------------------DOWN-Left-------------------------
		if (current_pos.x - 1 >= 0 && current_pos.y + 2 < 8) {
			if (_board.get_all_cells(current_pos.x - 1, current_pos.y + 2).get_employment() == false) {
				_board.get_all_cells(current_pos.x - 1, current_pos.y + 2).on_backlight();
			}
			else if (_board.get_all_cells(current_pos.x - 1, current_pos.y + 2).get_piece_color() != color) {
				_board.get_all_cells(current_pos.x - 1, current_pos.y + 2).on_backlight();
			}
		}
		//-------------------UP-RIGHT-------------------------
		if (current_pos.x + 1 < 8 && current_pos.y - 2 >= 0) {
			if (_board.get_all_cells(current_pos.x + 1, current_pos.y - 2).get_employment() == false) {
				_board.get_all_cells(current_pos.x + 1, current_pos.y - 2).on_backlight();
			}
			else if (_board.get_all_cells(current_pos.x + 1, current_pos.y - 2).get_piece_color() != color) {
				_board.get_all_cells(current_pos.x + 1, current_pos.y - 2).on_backlight();
			}
		}
		//--------------------UP-LEFT------------------------
		if (current_pos.x - 1 >= 0 && current_pos.y - 2 >= 0) {
			if (_board.get_all_cells(current_pos.x - 1, current_pos.y - 2).get_employment() == false) {
				_board.get_all_cells(current_pos.x - 1, current_pos.y - 2).on_backlight();
			}
			else if (_board.get_all_cells(current_pos.x - 1, current_pos.y - 2).get_piece_color() != color) {
				_board.get_all_cells(current_pos.x - 1, current_pos.y - 2).on_backlight();
			}
		}
		//-------------------RIGHT-UP-------------------------
		if (current_pos.x + 2 < 8 && current_pos.y - 1 >= 0) {
			if (_board.get_all_cells(current_pos.x + 2, current_pos.y - 1).get_employment() == false) {
				_board.get_all_cells(current_pos.x + 2, current_pos.y - 1).on_backlight();
			}
			else if (_board.get_all_cells(current_pos.x + 2, current_pos.y - 1).get_piece_color() != color) {
				_board.get_all_cells(current_pos.x + 2, current_pos.y - 1).on_backlight();
			}
		}
		//-------------------RIGHT-DOWN-------------------------
		if (current_pos.x + 2 < 8 && current_pos.y + 1 < 8) {
			if (_board.get_all_cells(current_pos.x + 2, current_pos.y + 1).get_employment() == false) {
				_board.get_all_cells(current_pos.x + 2, current_pos.y + 1).on_backlight();
			}
			else if (_board.get_all_cells(current_pos.x + 2, current_pos.y + 1).get_piece_color() != color) {
				_board.get_all_cells(current_pos.x + 2, current_pos.y + 1).on_backlight();
			}
		}
		//-------------------LEFT-UP-------------------------
		if (current_pos.x - 2 >= 0 && current_pos.y - 1 >= 0) {
			if (_board.get_all_cells(current_pos.x - 2, current_pos.y - 1).get_employment() == false) {
				_board.get_all_cells(current_pos.x - 2, current_pos.y - 1).on_backlight();
			}
			else if (_board.get_all_cells(current_pos.x - 2, current_pos.y - 1).get_piece_color() != color) {
				_board.get_all_cells(current_pos.x - 2, current_pos.y - 1).on_backlight();
			}
		}
		//--------------------LEFT-DOWN------------------------
		if (current_pos.x - 2 >= 0 && current_pos.y + 1 < 8) {
			if (_board.get_all_cells(current_pos.x - 2, current_pos.y + 1).get_employment() == false) {
				_board.get_all_cells(current_pos.x - 2, current_pos.y + 1).on_backlight();
			}
			else if (_board.get_all_cells(current_pos.x - 2, current_pos.y + 1).get_piece_color() != color) {
				_board.get_all_cells(current_pos.x - 2, current_pos.y + 1).on_backlight();
			}
		}
	}

	void change_position(int _x, int _y) override {
		position.x = _x;
		position.y = _y;
		sprite.setPosition(coord_trans(position).x, coord_trans(position).y);
	}
	void draw_piece(sf::RenderWindow &_window) override {
		_window.draw(sprite);
	}

private:
	sf::Texture texture;//(не изменяется, кроме пешек)
	sf::Sprite sprite;//(не изменяется, кроме пешек)
};