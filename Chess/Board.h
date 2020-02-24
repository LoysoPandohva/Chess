#pragma once
#include "Cell.h"

class Board {
public:
	Board();

	void off_backlight();

	Cell &get_all_cells(int _x, int _y);

	void draw_board_for_white(sf::RenderWindow &_window);
	void draw_board_for_black(sf::RenderWindow &_window);

private:
	Cell all_cells[8][8];
};