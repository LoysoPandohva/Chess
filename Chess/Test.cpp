#include "Server.h"
#include "Client.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(630, 500), "Chess");

	Client client;
	Server server;
	if (client.start_client()) {
		Pieces_on_board pob;
		Player_action player_action(pob, true);
		client.handle(window, pob, player_action);
	}
	else {
		Pieces_on_board pob;
		Player_action player_action(pob, false);
		server.startServer();
		server.handle(window, pob, player_action);
	}
}