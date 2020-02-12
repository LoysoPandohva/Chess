#include <SFML/Graphics.hpp>

#include "Player_action.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "Chess");

	Pieces_on_board pob;
	Player_action player_action(pob);

	while (window.isOpen())	{
		sf::Event event;
		window.pollEvent(event);

		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			window.close();

		player_action.get_cursor().action();
		player_action.selecting_piece(pob);
		player_action.make_move(pob,window);

		window.clear(sf::Color(200, 200, 200));

		pob.draw(window);
		player_action.get_cursor().draw(window);
		window.display();
	}
}