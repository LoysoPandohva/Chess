#include "Server.h"
#include "Client.h"

std::string enter_IP(sf::RenderWindow &_window) {
	sf::Font font;
	font.loadFromFile("Font//cour.ttf");
	sf::Text t[2];
	for (size_t i = 0; i < 2; i++) {
		t[i].setString("");
		t[i].setFont(font);
		t[i].setCharacterSize(30);
		t[i].setFillColor(sf::Color::Black);
		t[i].setStyle(sf::Text::Bold);
	}
	t[0].setPosition(20, 210);
	t[0].setString("Enter IP your opponent:");
	t[1].setPosition(20, 260);

	std::string str;

	bool single_press = false;
	sf::Event event;
	sf::Event event_for_text;
	while (_window.isOpen()) {
		_window.clear(sf::Color(200, 200, 200));
		_window.draw(t[0]);
		_window.draw(t[1]);
		_window.display();

		_window.pollEvent(event);
		_window.pollEvent(event_for_text);
		if (single_press == false) {
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					break;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
					if (!str.empty()) {
						str.pop_back();
						t[1].setString(str);
					}
				}
				else if (event_for_text.type == sf::Event::TextEntered) {
					if (event_for_text.text.unicode >= 48 && event_for_text.text.unicode < 58 || event_for_text.text.unicode == 46) {
						str += static_cast<char>(event_for_text.text.unicode);
						t[1].setString(str);
					}
				}
				single_press = true;
			}
		}
		else if (event.type == sf::Event::KeyReleased) single_press = false;
	}
	return str;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(630, 500), "Chess");
	std::string ip = enter_IP(window);
	Client client;
	if (client.start_client(ip.data())) {
		Pieces_on_board pob;
		Game game(pob, true);
		client.handle(window, game);
	}
	else {
		Server server;
		Pieces_on_board pob;
		Game game(pob, false);
		server.startServer();
		server.handle(window, game);
	}
}