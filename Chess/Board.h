#pragma once
#include "Cell.h"

class Board {
public:
	Board();

	void off_backlight() {
		for (size_t i = 0; i < 8; i++) {
			for (size_t j = 0; j < 8; j++) {
				all_cells[i][j].off_backlight();
			}
		}
	}

	Cell &get_all_cells(int _x, int _y);
	void draw_board_for_white(sf::RenderWindow &_window);
	void draw_board_for_black(sf::RenderWindow &_window);

private:
	Cell all_cells[8][8];
};