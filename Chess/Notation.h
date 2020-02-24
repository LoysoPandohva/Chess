#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

#include "Pieces_on_board.h"

class Notation {
public:
	Notation(const char* _filename);

	void add_move(Pieces_on_board &_pob, bool _whose_move);

	void cut_file();

	void made_move_back(Pieces_on_board &_pob, bool &_whose_move);
	void move_back(Pieces_on_board &_pob, bool &_whose_move);

	void continue_game(Pieces_on_board &_pob, bool &_whose_move);

	void set_count_moves(unsigned int _count_moves);
	unsigned int get_count_moves();
private:
	const char *filename;
	unsigned int count_moves;
	std::fstream notation;
};