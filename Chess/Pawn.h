#pragma once
#include "Piece.h"

class Pawn: public Piece {
public:
	Pawn(bool _color, int _x, int _y): Piece(_color, _x, _y) {
		texture.loadFromFile("images//pieces.png");
		sprite.setTexture(texture);
		if(color == false) sprite.setTextureRect(sf::IntRect(0, 1, 30, 48));
		else sprite.setTextureRect(sf::IntRect(150, 51, 30, 48));
		sprite.setPosition(coord_trans(position).x, coord_trans(position).y);
	}

	void possible_move(Board &_board) {
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