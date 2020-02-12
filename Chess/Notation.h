#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

#include "Pieces_on_board.h"

class Notation {
public:
	Notation(const char* _filename): filename(_filename), count_moves(0) {
		notation.open(filename, std::ios_base::out);
		notation.close();
	}

	void add_move(Pieces_on_board &_pob, bool _whose_move) {
		notation.open(filename, std::ios_base::app);
		notation << "Move ¹" << "_" << count_moves << "\n";
		notation << _whose_move << "\n";
		notation << _pob.get_pieces().size() << "\n";
		for (auto &p : _pob.get_pieces()) {
			notation << typeid(*p.get()).name() << ":" << p->get_color() << " " << p->get_first_move()
				<< " " << p->get_position().x << " " << p->get_position().y << "\n";
		}
		notation << "\n";
		notation.close();
		count_moves++;
	}

	void made_move_back(Pieces_on_board &_pob, bool &_whose_move) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				if (count_moves > 1) {
					move_back(_pob, _whose_move);
				}
			}
		}
	}

	void cut_file() {
		notation.open(filename);
		std::stringstream buf;
		std::string str;
		for (size_t i = 0; i < count_moves - 1; i++) {
			getline(notation, str, '\n');
			buf << str << '\n';
			getline(notation, str, '\n');
			buf << str << '\n';
			getline(notation, str, '\n');
			buf << str << '\n';
			size_t size = std::stoi(str);
			for (size_t j = 0; j < size; j++) {
				getline(notation, str, '\n');
				buf << str << '\n';
			}
			getline(notation, str, '\n');
			buf << '\n';
		}
		notation.close();

		notation.open(filename, std::ios_base::out);
		notation.close();

		notation.open(filename, std::ios_base::app);
		notation << buf.str();
		notation.close();

		count_moves--;
	}
	void move_back(Pieces_on_board &_pob, bool &_whose_move) {
		_pob.get_pieces().clear();

		if (count_moves > 1) {
			cut_file();
		}
		
		notation.open(filename);

		std::string str;
		for (size_t i = 0; i < count_moves - 1; i++) {
			getline(notation, str, '\n');
			getline(notation, str, '\n');
			getline(notation, str, '\n');
			size_t size = std::stoi(str);
			for (size_t j = 0; j < size; j++) {
				getline(notation, str, '\n');
			}
			getline(notation, str, '\n');
		}

		getline(notation, str, '\n');
		getline(notation, str, '\n');
		_whose_move = std::stoi(str);
		getline(notation, str, '\n');
		size_t size = std::stoi(str);
		for (size_t i = 0; i < size; i++) {
			getline(notation, str, ':');
			std::string type = str;
			getline(notation, str, ' ');
			bool color = std::stoi(str);
			getline(notation, str, ' ');
			bool first_move = std::stoi(str);
			getline(notation, str, ' ');
			int x = std::stoi(str);
			getline(notation, str, '\n');
			int y = std::stoi(str);
			if (strcmp(type.data(), "class Pawn") == 0) {
				_pob.get_pieces().push_back(std::make_shared<Pawn>(color, first_move, x, y));
			}
			if (strcmp(type.data(), "class Rook") == 0) {
				_pob.get_pieces().push_back(std::make_shared<Rook>(color, first_move, x, y));
			}
			if (strcmp(type.data(), "class Bishop") == 0) {
				_pob.get_pieces().push_back(std::make_shared<Bishop>(color, first_move, x, y));
			}
			if (strcmp(type.data(), "class Knight") == 0) {
				_pob.get_pieces().push_back(std::make_shared<Knight>(color, first_move, x, y));
			}
			if (strcmp(type.data(), "class King") == 0) {
				_pob.get_pieces().push_back(std::make_shared<King>(color, first_move, x, y));
			}
			if (strcmp(type.data(), "class Queen") == 0) {
				_pob.get_pieces().push_back(std::make_shared<Queen>(color, first_move, x, y));
			}
		}
		getline(notation, str, '\n');
		notation.close();

		for (size_t i = 0; i < 8; i++) {
			for (size_t j = 0; j < 8; j++) {
				_pob.get_board().get_all_cells(i, j).free_cell();
			}
		}
		for (auto &p : _pob.get_pieces()) {
			_pob.get_board().get_all_cells(p->get_position().x, p->get_position().y).employment_cell(p->get_color());
		}
	}

private:
	const char *filename;
	unsigned int count_moves;
	std::fstream notation;
};