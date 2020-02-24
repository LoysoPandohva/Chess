#pragma once
#include "Notation.h"
#include "Cursor.h"

class Game {
public:
	Game(Pieces_on_board &_pob, bool _your_color);

	void selecting_piece(sf::RenderWindow &_window, Pieces_on_board &_pob);

	void eat(Pieces_on_board &_pob);
	void change_position(Pieces_on_board &_pob, sf::RenderWindow  &_window);
	void make_move(Pieces_on_board &_pob, sf::RenderWindow  &_window);

	void opponent_eat(sf::Vector2i _to);
	void opponent_change_position(sf::Vector2i _to, int _new_piece);
	void opponent_move(sf::Vector2i _from, sf::Vector2i _to, int _new_piece, sf::RenderWindow  &_window);

	bool between_rook_and_king(Pieces_on_board &_pob, std::shared_ptr<Piece> &_s_p, std::shared_ptr<Piece> _p);
	void possible_castling(Pieces_on_board &_pob);
	void castling(Pieces_on_board &_pob, int _x, int _y);

	void move_back_and_notificaion(Pieces_on_board &_pob, sf::RenderWindow  &_window);

	std::shared_ptr<Piece> shah(Pieces_on_board &_pob, sf::RenderWindow  &_window);

	bool checkmate(Pieces_on_board &_pob, std::shared_ptr<Piece> &_king);
	bool check_all_possible_moves(Pieces_on_board &_pob, std::shared_ptr<Piece> &_piece, std::shared_ptr<Piece> &_king);
	bool check_move(Pieces_on_board &_pob, std::shared_ptr<Piece> &_king);

	void notificaion(sf::RenderWindow &_window, const char* _notification, int _fontsize);

	Cursor &get_cursor();
	bool get_your_color();
	bool get_whose_move();
	void change_move();
	std::shared_ptr<Piece> &get_king_who_shah();
	bool get_end();
	Pieces_on_board &get_pob();

	sf::Vector2i last_pos;
	sf::Vector2i new_pos;
	int new_piece;
private:
	Pieces_on_board &_pob;
	Cursor cursor;
	Notation notation;

	bool your_color;
	bool whose_move;

	std::shared_ptr<Piece> select_piece;
	bool piece_is_select;

	std::shared_ptr<Piece> king_who_shah;
	bool end;
};