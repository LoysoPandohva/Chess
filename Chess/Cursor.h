#pragma once
#include <SFML/Graphics.hpp>

#include "Pieces_on_board.h"

class Cursor {
public:
	Cursor(): piece_is_select(false) {
		cursor.setRadius(15);
		cursor.setFillColor(unselect);
		cursor.setPosition(235, 235);
	}
	void action() {
		float speed = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { speed = 5; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			cursor.move(0, -speed);
			if (cursor.getPosition().y + 15 < 50) {
				cursor.move(0, speed);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			cursor.move(speed, 0);
			if (cursor.getPosition().x + 15 > 450) {
				cursor.move(-speed, 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			cursor.move(0, speed);
			if (cursor.getPosition().y + 15 > 450) {
				cursor.move(0, -speed);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			cursor.move(-speed, 0);
			if (cursor.getPosition().x + 15 < 50) {
				cursor.move(speed, 0);
			}
		}
	}

	sf::Vector2i selected_cell() {
		return sf::Vector2i(static_cast<int>(cursor.getPosition().x + 15) / 50 - 1,
			static_cast<int>(cursor.getPosition().y + 15) / 50 - 1);
	}
	void selecting_piece(Pieces_on_board &_pob) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && piece_is_select == true) {
			cursor.setFillColor(unselect);
			_pob.get_board().off_backlight();
			select_piece = nullptr;
			piece_is_select = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && piece_is_select == false) {
			if (_pob.get_board().get_all_cells(selected_cell().x, selected_cell().y).get_employment() == true) {
				cursor.setFillColor(select);
				for (auto &p : _pob.get_pieces()) {
					if (p->get_position().x == selected_cell().x && p->get_position().y == selected_cell().y) {
						select_piece = p;
						select_piece->possible_move(_pob.get_board());
						piece_is_select = true;
						break;
					}
				}
			}
		}
	}

	void eat(Pieces_on_board &_pob) {
		if (_pob.get_board().get_all_cells(selected_cell().x, selected_cell().y).get_employment() == 1) {
			if (_pob.get_board().get_all_cells(selected_cell().x, selected_cell().y).get_piece_color() !=
				select_piece->get_color()) {
				for (auto &p : _pob.get_pieces()) {
					if (p->get_position().x == selected_cell().x && p->get_position().y == selected_cell().y) {
						_pob.kill_piece(p);
						break;
					}
				}
			}
		}
	}
	void change_position(Pieces_on_board &_pob) {
		if (_pob.get_board().get_all_cells(selected_cell().x, selected_cell().y).get_employment() == 0) {
			_pob.get_board().get_all_cells(select_piece->get_position().x, select_piece->get_position().y).free_cell();

			select_piece->change_position(selected_cell().x, selected_cell().y);
			_pob.get_board().get_all_cells(selected_cell().x, selected_cell().y).employment_cell(select_piece->get_color());

			select_piece->make_first_move();
			cursor.setFillColor(unselect);
			_pob.get_board().off_backlight();
			select_piece = nullptr;
			piece_is_select = false;
		}
	}
	void make_move(Pieces_on_board &_pob) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && piece_is_select == true) {
			eat(_pob);
			change_position(_pob);
		}
	}

	void draw(sf::RenderWindow  &_window) {
		_window.draw(cursor);
	}

	static const sf::Color select;
	static const sf::Color unselect;

private:
	std::shared_ptr<Piece> select_piece;
	sf::CircleShape cursor;
	bool piece_is_select;
};