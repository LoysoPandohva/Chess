#pragma once
#include <list>
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
			pob.push_back(std::make_shared<Pawn>(false, i, 1));
		}
		pob.push_back(std::make_shared<Rook>(false, 0, 0));
		pob.push_back(std::make_shared<Bishop>(false, 1, 0));
		pob.push_back(std::make_shared<Knight>(false, 2, 0));
		pob.push_back(std::make_shared<King>(false, 3, 0));
		pob.push_back(std::make_shared<Queen>(false, 4, 0));
		pob.push_back(std::make_shared<Knight>(false, 5, 0));
		pob.push_back(std::make_shared<Bishop>(false, 6, 0));
		pob.push_back(std::make_shared<Rook>(false, 7, 0));
		for (size_t i = 0; i < 8; i++) {
			pob.push_back(std::make_shared<Pawn>(true, i, 6));
		}
		pob.push_back(std::make_shared<Rook>(true, 0, 7));
		pob.push_back(std::make_shared<Bishop>(true, 1, 7));
		pob.push_back(std::make_shared<Knight>(true, 2, 7));
		pob.push_back(std::make_shared<King>(true, 3, 7));
		pob.push_back(std::make_shared<Queen>(true, 4, 7));
		pob.push_back(std::make_shared<Knight>(true, 5, 7));
		pob.push_back(std::make_shared<Bishop>(true, 6, 7));
		pob.push_back(std::make_shared<Rook>(true, 7, 7));

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