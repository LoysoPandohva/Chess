#pragma once
#include "Notation.h"
#include "Cursor.h"
#include "Mouse_cursor.h"

class Player_action {
public:
	Player_action(Pieces_on_board &_pob, bool _your_color) : _pob(_pob), cursor(), your_color(_your_color), piece_is_select(false),
		whose_move(false), notation("notation.txt"), end(false) {
		notation.add_move(_pob, whose_move);
	}

	void selecting_piece(sf::RenderWindow &_window, Pieces_on_board &_pob) {
		//notation.made_move_back(_pob, whose_move);

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && piece_is_select == true) {
			cursor.get_cursor().setFillColor(Cursor::unselect);
			_pob.get_board().off_backlight();
			select_piece = nullptr;
			piece_is_select = false;
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && piece_is_select == false) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				cursor.set_cursor(sf::Vector2f((float)m_cursor.get_mause_pos(_window).x, (float)m_cursor.get_mause_pos(_window).y));
			}
			sf::Vector2i sel_cell;
			if (your_color == true) {
				sel_cell = sf::Vector2i(cursor.selected_cell().x, cursor.selected_cell().y);
			}
			else {
				sel_cell = sf::Vector2i(7 - cursor.selected_cell().x, 7 - cursor.selected_cell().y);
			}
			if (_pob.get_board().get_all_cells(sel_cell.x, sel_cell.y).get_employment() == true) {
				if (_pob.get_board().get_all_cells(sel_cell.x, sel_cell.y).get_piece_color() == your_color) {
					cursor.get_cursor().setFillColor(Cursor::select);
					for (auto &p : _pob.get_pieces()) {
						if (p->get_position().x == sel_cell.x && p->get_position().y == sel_cell.y) {
							select_piece = p;
							select_piece->possible_move(_pob.get_board());
							possible_castling(_pob);
							piece_is_select = true;
							break;
						}
					}
				}
			}
		}
	}

	void eat(Pieces_on_board &_pob) {
		sf::Vector2i sel_cell;
		if (your_color == true) {
			sel_cell = sf::Vector2i(cursor.selected_cell().x, cursor.selected_cell().y);
		}
		else {
			sel_cell = sf::Vector2i(7 - cursor.selected_cell().x, 7 - cursor.selected_cell().y);
		}
		if (_pob.get_board().get_all_cells(sel_cell.x, sel_cell.y).get_employment() == true) {
			if (_pob.get_board().get_all_cells(sel_cell.x, sel_cell.y).get_piece_color() !=
				select_piece->get_color()) {
				for (auto &p : _pob.get_pieces()) {
					if (p->get_position().x == sel_cell.x && p->get_position().y == sel_cell.y) {
						_pob.kill_piece(p);
						break;
					}
				}
			}
		}
	}
	void change_position(Pieces_on_board &_pob, sf::RenderWindow  &_window) {
		sf::Vector2i sel_cell;
		if (your_color == true) {
			sel_cell = sf::Vector2i(cursor.selected_cell().x, cursor.selected_cell().y);
		}
		else {
			sel_cell = sf::Vector2i(7 - cursor.selected_cell().x, 7 - cursor.selected_cell().y);
		}
		if (_pob.get_board().get_all_cells(sel_cell.x, sel_cell.y).get_employment() == false) {
			last_pos.x = select_piece->get_position().x;
			last_pos.y = select_piece->get_position().y;
			new_pos.x = sel_cell.x;
			new_pos.y = sel_cell.y;
			new_piece = 0;

			_pob.get_board().get_all_cells(select_piece->get_position().x, select_piece->get_position().y).free_cell();

			select_piece->change_position(sel_cell.x, sel_cell.y);
			_pob.get_board().get_all_cells(sel_cell.x, sel_cell.y).employment_cell(select_piece->get_color());



			if (strcmp(typeid(*select_piece.get()).name(), "class Pawn") == 0) {
				new_piece = _pob.select_piece_for_replacement(_window, select_piece);
			}
			select_piece->make_first_move();

			cursor.get_cursor().setFillColor(Cursor::unselect);
			_pob.get_board().off_backlight();

			select_piece = nullptr;
			piece_is_select = false;
			change_move();

			notation.add_move(_pob, whose_move);
		}
	}
	void make_move(Pieces_on_board &_pob, sf::RenderWindow  &_window) {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) && piece_is_select == true) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				cursor.set_cursor(sf::Vector2f((float)m_cursor.get_mause_pos(_window).x, (float)m_cursor.get_mause_pos(_window).y));
			}
			sf::Vector2i sel_cell;
			if (your_color == true) {
				sel_cell = sf::Vector2i(cursor.selected_cell().x, cursor.selected_cell().y);
			}
			else {
				sel_cell = sf::Vector2i(7 - cursor.selected_cell().x, 7 - cursor.selected_cell().y);
			}
			if (_pob.get_board().get_all_cells(sel_cell.x, sel_cell.y).get_backlight() == true) {
				eat(_pob);
				change_position(_pob, _window);
				castling(_pob, sel_cell.x, sel_cell.y);

				if (shah(_pob, _window)) {
					if (checkmate(_pob, king_who_shah) == true) {
						end = true;
					}
				}
			}
		}
	}

	void opponent_eat(sf::Vector2i _to) {
		if (_pob.get_board().get_all_cells(_to.x, _to.y).get_employment() == true) {
			if (_pob.get_board().get_all_cells(_to.x, _to.y).get_piece_color() != select_piece->get_color()) {
				for (auto &p : _pob.get_pieces()) {
					if (p->get_position().x == _to.x && p->get_position().y == _to.y) {
						_pob.kill_piece(p);
						break;
					}
				}
			}
		}
	}
	void opponent_change_position(sf::Vector2i _to, int _new_piece) {
		if (_pob.get_board().get_all_cells(_to.x, _to.y).get_employment() == false) {
			_pob.get_board().get_all_cells(select_piece->get_position().x, select_piece->get_position().y).free_cell();
			select_piece->change_position(_to.x, _to.y);
			_pob.get_board().get_all_cells(_to.x, _to.y).employment_cell(select_piece->get_color());

			if (strcmp(typeid(*select_piece.get()).name(), "class Pawn") == 0) {
				_pob.pawn_replacement(select_piece, _new_piece);
			}

			select_piece->make_first_move();
			change_move();
			notation.add_move(_pob, whose_move);
			select_piece = nullptr;
		}
	}
	void opponent_move(sf::Vector2i _from, sf::Vector2i _to, int _new_piece, sf::RenderWindow  &_window) {
		for (auto &p : _pob.get_pieces()) {
			if (p->get_position().x == _from.x && p->get_position().y == _from.y) {
				select_piece = p;
				break;
			}
		}

		opponent_eat(_to);
		opponent_change_position(_to, _new_piece);
		castling(_pob, _to.x, _to.y);

		if (shah(_pob, _window)) {
			if (checkmate(_pob, king_who_shah) == true) {
				end = true;
			}
		}
	}

	bool between_rook_and_king(Pieces_on_board &_pob, std::shared_ptr<Piece> &_s_p, std::shared_ptr<Piece> _p) {
		if (_s_p->get_position().x < _p->get_position().x) {
			if (_pob.get_board().get_all_cells(_s_p->get_position().x + 1, _s_p->get_position().y).get_employment() == true) {
				return false;
			}
			if (_pob.get_board().get_all_cells(_s_p->get_position().x + 2, _s_p->get_position().y).get_employment() == true) {
				return false;
			}
			if (_pob.get_board().get_all_cells(_s_p->get_position().x + 3, _s_p->get_position().y).get_employment() == true) {
				return false;
			}
		}
		else if (_s_p->get_position().x > _p->get_position().x) {
			if (_pob.get_board().get_all_cells(_s_p->get_position().x - 1, _s_p->get_position().y).get_employment() == true) {
				return false;
			}
			if (_pob.get_board().get_all_cells(_s_p->get_position().x - 2, _s_p->get_position().y).get_employment() == true) {
				return false;
			}
		}
		return true;
	}
	void possible_castling(Pieces_on_board &_pob) {
		if (strcmp(typeid(*select_piece.get()).name(), "class King") == 0) {
			if (select_piece->get_first_move() == false) {
				for (const auto &p : _pob.get_pieces()) {
					if (select_piece->get_color() == p->get_color()) {
						if (strcmp(typeid(*p.get()).name(), "class Rook") == 0) {
							if (p->get_first_move() == false) {
								if (between_rook_and_king(_pob, select_piece, p) == true) {
									_pob.get_board().get_all_cells(p->get_position().x, p->get_position().y).on_backlight();
								}
							}
						}
					}
				}
			}
		}
	}
	void castling(Pieces_on_board &_pob, int _x, int _y) {
		if (select_piece != nullptr) {
			for (auto &p : _pob.get_pieces()) {
				if (p->get_position().x == _x && p->get_position().y == _y) {
					last_pos.x = select_piece->get_position().x;
					last_pos.y = select_piece->get_position().y;
					new_pos.x = _x;
					new_pos.y = _y;
					new_piece = 0;

					_pob.get_board().get_all_cells(p->get_position().x, p->get_position().y).free_cell();
					_pob.get_board().get_all_cells(select_piece->get_position().x, select_piece->get_position().y).free_cell();
					if (p->get_position().x > select_piece->get_position().x) {
						select_piece->change_position(select_piece->get_position().x + 3, select_piece->get_position().y);
						_pob.get_board().get_all_cells(select_piece->get_position().x, select_piece->get_position().y)
							.employment_cell(select_piece->get_color());
						p->change_position(p->get_position().x - 2, p->get_position().y);
						_pob.get_board().get_all_cells(p->get_position().x, p->get_position().y).employment_cell(select_piece->get_color());
					}
					else if (p->get_position().x < select_piece->get_position().x) {
						select_piece->change_position(select_piece->get_position().x - 2, select_piece->get_position().y);
						_pob.get_board().get_all_cells(select_piece->get_position().x, select_piece->get_position().y)
							.employment_cell(select_piece->get_color());
						p->change_position(p->get_position().x + 2, p->get_position().y);
						_pob.get_board().get_all_cells(p->get_position().x, p->get_position().y).employment_cell(select_piece->get_color());
					}
					select_piece->make_first_move();
					cursor.get_cursor().setFillColor(Cursor::unselect);
					_pob.get_board().off_backlight();
					select_piece = nullptr;
					piece_is_select = false;
					change_move();
					break;
				}
			}
		}
	}

	void move_back_and_notificaion(Pieces_on_board &_pob, sf::RenderWindow  &_window) {
		_pob.get_board().off_backlight();
		notation.move_back(_pob, whose_move);
		king_who_shah = nullptr;
		shah(_pob, _window);
		_pob.get_board().off_backlight();
		notificaion(_window, "You must protect\n    the king!", 15);
	}

	std::shared_ptr<Piece> shah(Pieces_on_board &_pob, sf::RenderWindow  &_window) {
		for (auto &p : _pob.get_pieces()) {
			p->possible_move(_pob.get_board());
		}
		for (auto &p : _pob.get_pieces()) {
			if (strcmp(typeid(*p.get()).name(), "class King") == 0) {
				if (_pob.get_board().get_all_cells(p->get_position().x, p->get_position().y).get_backlight() == true) {
					if (king_who_shah == p) {
						move_back_and_notificaion(_pob, _window);
						return nullptr;
					}
					if (king_who_shah != p) {
						if (king_who_shah != nullptr) {
							if (_pob.get_board().get_all_cells(king_who_shah->get_position().x, king_who_shah->get_position().y).
								get_backlight() == true) {
								move_back_and_notificaion(_pob, _window);
								return nullptr;
							}
						}
					}
					if (p->get_color() != whose_move) {
						move_back_and_notificaion(_pob, _window);
						return nullptr;
					}
					king_who_shah = p;
					_pob.get_board().off_backlight();
					return king_who_shah;
				}
			}
		}
		king_who_shah = nullptr;
		_pob.get_board().off_backlight();
		return nullptr;
	}

	bool checkmate(Pieces_on_board &_pob, std::shared_ptr<Piece> &_king) {
		for (auto &p : _pob.get_pieces()) {
			if (p->get_color() == whose_move) {
				_pob.get_board().off_backlight();
				if (check_all_possible_moves(_pob, p, _king) == false) {
					_pob.get_board().off_backlight();
					return false;
				}
			}
		}
		_pob.get_board().off_backlight();
		return true;
	}
	bool check_all_possible_moves(Pieces_on_board &_pob, std::shared_ptr<Piece> &_piece, std::shared_ptr<Piece> &_king) {
		sf::Vector2i last_pos(_piece->get_position().x, _piece->get_position().y);

		std::shared_ptr<Piece> dead_piece = nullptr;
		_piece->possible_move(_pob.get_board());
		for (size_t y = 0; y < 8; y++) {
			for (size_t x = 0; x < 8; x++) {
				if (_pob.get_board().get_all_cells(x, y).get_backlight() == true) {

					if (_pob.get_board().get_all_cells(x, y).get_employment() == true) {
						if (_pob.get_board().get_all_cells(x, y).get_piece_color() != _piece->get_color()) {
							for (auto &p : _pob.get_pieces()) {
								if (p->get_position().x == x && p->get_position().y == y) {
									dead_piece = p;
									_pob.kill_piece(p);
									break;
								}
							}
						}
					}

					if (_pob.get_board().get_all_cells(x, y).get_employment() == false) {
						_pob.get_board().get_all_cells(_piece->get_position().x, _piece->get_position().y).free_cell();
						_piece->change_position(x, y);
						_pob.get_board().get_all_cells(x, y).employment_cell(_piece->get_color());

						bool is_mate = true;
						if (check_move(_pob, _king) == false) {
							is_mate = false;
						}

						_pob.get_board().get_all_cells(x, y).free_cell();
						_piece->change_position(last_pos.x, last_pos.y);
						_pob.get_board().get_all_cells(last_pos.x, last_pos.y).employment_cell(_piece->get_color());
						if (dead_piece != nullptr) {
							_pob.get_pieces().push_back(dead_piece);
							_pob.get_board().get_all_cells(dead_piece->get_position().x, dead_piece->get_position().y).employment_cell(dead_piece->get_color());
							dead_piece = nullptr;
						}

						if (is_mate == false) return false;

						_piece->possible_move(_pob.get_board());
					}
				}
			}
		}
		return true;
	}
	bool check_move(Pieces_on_board &_pob, std::shared_ptr<Piece> &_king) {
		_pob.get_board().off_backlight();
		for (auto &p : _pob.get_pieces()) {
			p->possible_move(_pob.get_board());
		}
		if (_pob.get_board().get_all_cells(_king->get_position().x, _king->get_position().y).get_backlight() == false) {
			_pob.get_board().off_backlight();
			return false;
		}
		_pob.get_board().off_backlight();
		return true;
	}

	void notificaion(sf::RenderWindow &_window, const char* _notification, int _fontsize) {
		sf::RectangleShape shape(sf::Vector2f(180, 90));
		shape.setFillColor(sf::Color(0, 0, 0, 255));
		shape.setPosition(160, 205);

		sf::Font font;
		font.loadFromFile("Font//cour.ttf");
		sf::Text t[2];
		t[0].setString(_notification);
		t[0].setFont(font);
		t[0].setCharacterSize(_fontsize);
		t[0].setPosition(160 + 9, 215);
		t[0].setFillColor(sf::Color::White);
		t[0].setStyle(sf::Text::Bold);

		t[1].setString("press ENTER to continue");
		t[1].setFont(font);
		t[1].setCharacterSize(12);
		t[1].setPosition(160 + 17, 280);
		t[1].setFillColor(sf::Color::White);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		sf::Event event;
		while (true) {
			_window.clear(sf::Color(200, 200, 200));

			if (your_color == false) {
				_pob.draw_for_white(_window);
			}
			else {
				_pob.draw_for_black(_window);
			}
			cursor.draw(_window);

			_window.draw(shape);
			for (int i = 0; i < 2; i++) {
				_window.draw(t[i]);
			}

			_window.display();

			_window.pollEvent(event);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				break;
			}
		}
	}

	sf::Vector2i last_pos;
	sf::Vector2i new_pos;
	int new_piece;


	Cursor &get_cursor() {
		return cursor;
	}
	bool get_whose_move() {
		return whose_move;
	}
	void change_move() {
		whose_move = !whose_move;
	}
	std::shared_ptr<Piece> &get_king_who_shah() {
		return king_who_shah;
	}
	bool get_end() {
		return end;
	}
	Pieces_on_board &get_pob() {
		return _pob;
	}
private:
	Pieces_on_board &_pob;
	Cursor cursor;
	Mouse_cursor m_cursor;
	Notation notation;
	bool your_color;
	bool whose_move;

	std::shared_ptr<Piece> select_piece;
	bool piece_is_select;

	std::shared_ptr<Piece> king_who_shah;
	bool end;
};