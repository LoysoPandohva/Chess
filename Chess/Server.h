#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include "Game.h"

#include <WinSock2.h>
#include <winsock.h>
#include <thread>
#include <iostream>

class Server {
public:
	Server();
	~Server();

	void startServer();
	void closeServer();
	void close_app(sf::RenderWindow  &_window);

	void notification(sf::RenderWindow  &_window, const char _notification[]);

	void read_buf(sf::Vector2i &_from, sf::Vector2i &_to, int &_type_piece, char _buf[], int _size);
	void write_buf(char _buf[], int _size, sf::Vector2i &_last_pos, sf::Vector2i &_new_pos, int &_type_piece);

	void listen_opponent(sf::RenderWindow  &_window, SOCKET &acceptS, Game &_game);

	void show_time(sf::RenderWindow  &_window, const char _your_time[], const char _opponent_time[], bool _your_color);
	void convert_time(int _time, char _res[]);
	char* your_time(bool _your_move, const int _game_time);
	char* opponent_time(bool _opponent_move, const int _game_time);

	void handle(sf::RenderWindow  &_window, Game &_game);

private:
	WSAData wData;
	SOCKET my_socket;
	unsigned short port;
	bool lose_connection;
};