#pragma once
#include <list>
#include <chrono>
#include <thread>
//#include <memory>

#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Board.h"

class Pieces_on_board {
public:
	Pieces_on_board(): board() {
		for (size_t i = 0; i < 8; i++) {
			pob.push_back(std::make_shared<Pawn>(false, false, i, 1));
		}
		pob.push_back(std::make_shared<Rook>(false, false, 0, 0));
		pob.push_back(std::make_shared<Knight>(false, false, 1, 0));
		pob.push_back(std::make_shared<Bishop>(false, false, 2, 0));
		pob.push_back(std::make_shared<King>(false, false, 3, 0));
		pob.push_back(std::make_shared<Queen>(false, false, 4, 0));
		pob.push_back(std::make_shared<Bishop>(false, false, 5, 0));
		pob.push_back(std::make_shared<Knight>(false, false, 6, 0));
		pob.push_back(std::make_shared<Rook>(false, false, 7, 0));
		for (size_t i = 0; i < 8; i++) {
			pob.push_back(std::make_shared<Pawn>(true, false, i, 6));
		}
		pob.push_back(std::make_shared<Rook>(true, false, 0, 7));
		pob.push_back(std::make_shared<Knight>(true, false, 1, 7));
		pob.push_back(std::make_shared<Bishop>(true, false, 2, 7));
		pob.push_back(std::make_shared<King>(true, false, 3, 7));
		pob.push_back(std::make_shared<Queen>(true, false, 4, 7));
		pob.push_back(std::make_shared<Bishop>(true, false, 5, 7));
		pob.push_back(std::make_shared<Knight>(true, false, 6, 7));
		pob.push_back(std::make_shared<Rook>(true, false, 7, 7));

		for (size_t i = 0; i < 8; i++) {
			board.get_all_cells(i, 0).employment_cell(false);
			board.get_all_cells(i, 1).employment_cell(false);
			board.get_all_cells(i, 6).employment_cell(true);
			board.get_all_cells(i, 7).employment_cell(true);
		}
	}
	
	void kill_piece(std::shared_ptr<Piece> &_piece) {
		board.get_all_cells(_piece->get_position().x, _piece->get_position().y).free_cell();
		pob.remove(_piece);
	}

	void pawn_replacement(std::shared_ptr<Piece> &_piece, int _select) {
		if (_piece->get_position().y == 7 || _piece->get_position().y == 0) {
			switch (_select) {
			case 1:
				pob.push_back(std::make_shared<Rook>(_piece->get_color(), _piece->get_first_move(), _piece->get_position().x, _piece->get_position().y));
				break;
			case 2:
				pob.push_back(std::make_shared<Knight>(_piece->get_color(), _piece->get_first_move(), _piece->get_position().x, _piece->get_position().y));
				break;
			case 3:
				pob.push_back(std::make_shared<Bishop>(_piece->get_color(), _piece->get_first_move(), _piece->get_position().x, _piece->get_position().y));
				break;
			case 4:
				pob.push_back(std::make_shared<Queen>(_piece->get_color(), _piece->get_first_move(), _piece->get_position().x, _piece->get_position().y));
				break;
			default:
				break;
			}
			kill_piece(_piece);
			get_board().get_all_cells(pob.back()->get_position().x, pob.back()->get_position().y).employment_cell(pob.back()->get_color());
		}
	}

	int select_piece_for_replacement(sf::RenderWindow &_window, std::shared_ptr<Piece> &_piece) {
		if (_piece->get_position().y == 7 || _piece->get_position().y == 0) {
			sf::RectangleShape shape(sf::Vector2f(160, 80));
			shape.setFillColor(sf::Color(0, 0, 0, 255));
			shape.setPosition(170, 210);

			sf::Font font;
			font.loadFromFile("Font//cour.ttf");
			sf::Text t[5];
			for (int i = 0; i < 5; i++) {
				t[i].setFont(font);
				t[i].setCharacterSize(15);
				t[i].setPosition(180 + 4, 210 + (float)i * 14);
				t[i].setFillColor(sf::Color::White);
				t[i].setStyle(sf::Text::Bold);
			}

			t[0].setString("Choose piece:");
			t[1].setString("Rook");
			t[2].setString("Knight");
			t[3].setString("Bishop");
			t[4].setString("Queen");

			sf::CircleShape triangle(6, 3);
			triangle.setRotation(90);
			triangle.setPosition(180 + 14, 210 + 19);
			triangle.setFillColor(sf::Color::White);

			int select = 1;
			t[select].move(13, 0);

			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			while (true) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					if (select + 1 <= 4) {
						t[select].move(-13, 0);
						select++;
						t[select].move(13, 0);
						triangle.move(0, 14);
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(180));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					if (select - 1 >= 1) {
						t[select].move(-13, 0);
						select--;
						t[select].move(13, 0);
						triangle.move(0, -14);
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(180));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					break;
				}

				_window.draw(shape);
				for (int i = 0; i < 5; i++) {
					_window.draw(t[i]);
				}
				_window.draw(triangle);
				_window.display();
			}
			pawn_replacement(_piece, select);
			return select;
		}
		return 0;
	}

	std::list<std::shared_ptr<Piece>> &get_pieces() {
		return pob;
	}
	Board &get_board() {
		return board;
	}
	void draw(sf::RenderWindow &_window) {
		board.draw_board(_window);
		for (const auto &p : pob) {
			p->draw_piece(_window);
		}
	}

private:
	

	std::list<std::shared_ptr<Piece>> pob;
	Board board;
};