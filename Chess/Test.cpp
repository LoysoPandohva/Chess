#include "Server.h"
//#include "Player_action.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "Chess");

	Pieces_on_board pob;
	Player_action player_action(pob);
	Server app;

	app.handle(window, pob, player_action);
}