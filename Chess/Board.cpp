#include "Board.h"

Board::Board() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			all_cells[i][j].set_position(((float)i + 1) * 50, ((float)j + 1) * 50);
			if ((i + j) % 2 == 1) all_cells[i][j].set_color(Cell::black);
			else all_cells[i][j].set_color(Cell::white);
		}
	}
}
Cell& Board::get_all_cells(int _x, int _y) {
	return all_cells[_x][_y];
}

void Board::draw_board_for_white(sf::RenderWindow &_window) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_window.draw(all_cells[i][j].get_cell());
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (all_cells[i][j].get_backlight() == 1) {
				sf::RectangleShape square_light(sf::Vector2f(50.f, 50.f));
				square_light.setPosition(((7 - i) + 1) * 50.f, ((7 - j) + 1) * 50.f);
				square_light.setFillColor(Cell::green);
				_window.draw(square_light);
			}
		}
	}

	sf::Font font;
	font.loadFromFile("Font//cour.ttf");
	sf::Text t[16];
	for (int i = 0; i < 16; i++) {
		t[i].setFont(font);
		t[i].setCharacterSize(35);
		t[i].setFillColor(sf::Color(0, 0, 0));
		t[i].setStyle(sf::Text::Bold);
	}
	t[0].setString("8");
	t[1].setString("7");
	t[2].setString("6");
	t[3].setString("5");
	t[4].setString("4");
	t[5].setString("3");
	t[6].setString("2");
	t[7].setString("1");
	t[8].setString("A");
	t[9].setString("B");
	t[10].setString("C");
	t[11].setString("D");
	t[12].setString("E");
	t[13].setString("F");
	t[14].setString("G");
	t[15].setString("H");

	for (int i = 0; i < 8; i++) {
		t[i].setPosition(15, (float)i * 50 + 50);
		_window.draw(t[i]);
		t[i].setPosition(465, (float)i * 50 + 50);
		_window.draw(t[i]);
	}
	for (int i = 8; i < 16; i++) {
		t[i].setPosition(((float)i - 8) * 50 + 62, 1);
		_window.draw(t[i]);
		t[i].setPosition(((float)i - 8) * 50 + 62, 451);
		_window.draw(t[i]);
	}
}
void Board::draw_board_for_black(sf::RenderWindow &_window) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_window.draw(all_cells[i][j].get_cell());
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (all_cells[i][j].get_backlight() == 1) {
				sf::RectangleShape square_light(sf::Vector2f(50.f, 50.f));
				square_light.setPosition((i + 1) * 50.f, (j + 1) * 50.f);
				square_light.setFillColor(Cell::green);
				_window.draw(square_light);
			}
		}
	}
	sf::Font font;
	font.loadFromFile("Font//cour.ttf");
	sf::Text t[16];
	for (int i = 0; i < 16; i++) {
		t[i].setFont(font);
		t[i].setCharacterSize(35);
		t[i].setFillColor(sf::Color(0, 0, 0));
		t[i].setStyle(sf::Text::Bold);
	}
	t[0].setString("8");
	t[1].setString("7");
	t[2].setString("6");
	t[3].setString("5");
	t[4].setString("4");
	t[5].setString("3");
	t[6].setString("2");
	t[7].setString("1");
	t[8].setString("A");
	t[9].setString("B");
	t[10].setString("C");
	t[11].setString("D");
	t[12].setString("E");
	t[13].setString("F");
	t[14].setString("G");
	t[15].setString("H");

	for (int i = 0; i < 8; i++) {
		t[i].setPosition(15, (float)(7 - i) * 50 + 50);
		_window.draw(t[i]);
		t[i].setPosition(465, (float)(7 - i) * 50 + 50);
		_window.draw(t[i]);
	}
	for (int i = 8; i < 16; i++) {
		t[i].setPosition(((float)(15 - i)) * 50 + 62, 1);
		_window.draw(t[i]);
		t[i].setPosition(((float)(15 - i)) * 50 + 62, 451);
		_window.draw(t[i]);
	}
}