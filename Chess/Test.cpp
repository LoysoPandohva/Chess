#include <SFML/Graphics.hpp>

#include "Pieces_on_board.h"
#include "Cursor.h"

int main() {
	// Создаем главное окно приложения
	sf::RenderWindow window(sf::VideoMode(500, 500), "Chess");

	Pieces_on_board pob;
	Cursor cursor;
	// Главный цикл приложения
	while (window.isOpen())	{
		// Обрабатываем события в цикле
		sf::Event event;
		window.pollEvent(event);
		//while (window.pollEvent(event)) {
		//	// Кроме обычного способа наше окно будет закрываться по нажатию на Escape
		//	if (event.type == sf::Event::Closed ||
		//		(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		//		window.close();
		//}

		// Тут будут вызываться функции обновления и отрисовки объектов
		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			window.close();
		cursor.action();
		cursor.selecting_piece(pob);
		cursor.make_move(pob);
		// Очистка
		window.clear(sf::Color(200, 200, 200));
		// Отрисовка
		pob.draw(window);
		cursor.draw(window);

		window.display();
	}
}