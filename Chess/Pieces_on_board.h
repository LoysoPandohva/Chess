#pragma once
#include <list>
#include <chrono>
#include <thread>

#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Board.h"

class Pieces_on_board {
public:
	Pieces_on_board();
	
	void kill_piece(std::shared_ptr<Piece> &_piece);

	void pawn_replacement(std::shared_ptr<Piece> &_piece, int _select);
	int select_piece_for_replacement(sf::RenderWindow &_window, std::shared_ptr<Piece> &_piece);

	std::list<std::shared_ptr<Piece>> &get_pieces();
	Board &get_board();

	void draw_for_white(sf::RenderWindow &_window);
	void draw_for_black(sf::RenderWindow &_window);

private:
	std::list<std::shared_ptr<Piece>> pob;
	Board board;
};