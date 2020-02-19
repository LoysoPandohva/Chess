#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include "Player_action.h"

#include <WinSock2.h>
#include <winsock.h>
#include <thread>
#include <iostream>

class Server {
public:
	Server() : port(27015) {}

	~Server() {
		closeServer();
	}

	void startServer() {
		if (WSAStartup(MAKEWORD(2, 2), &wData) == 0) {
			std::cout << "WSA Startup succes" << std::endl;
		}

		SOCKADDR_IN addr;
		int addrl = sizeof(addr);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;

		my_socket = socket(AF_INET, SOCK_STREAM, NULL);
		if (my_socket == SOCKET_ERROR) {
			std::cout << "Socket not created" << std::endl;
		}

		if (bind(my_socket, (struct sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR) {
			std::cout << "Socket succed binded" << std::endl;
		}

		if (listen(my_socket, SOMAXCONN) != SOCKET_ERROR) {
			std::cout << "Start listenin at port " << ntohs(addr.sin_port) << std::endl;
		}
	}

	void closeServer() {
		closesocket(my_socket);
		WSACleanup();
		std::cout << "Server was stoped. You can close app" << std::endl;
	}

	void read_buf(sf::Vector2i &_from, sf::Vector2i &_to, int &_type_piece, char _buf[], int _size) {
		char num[2];
		int index_sym = 0;
		int nums[5];
		int indesx_num = 0;
		for (int i = 0; i < _size - 1; i++) {
			num[0] = _buf[i];
			num[1] = 0;
			nums[indesx_num++] = atoi(num);
		}
		_from = sf::Vector2i(nums[0], nums[1]);
		_to = sf::Vector2i(nums[2], nums[3]);
		_type_piece = nums[4];
	}
	void serialize(char _buf[], int _size, sf::Vector2i &_last_pos, sf::Vector2i &_new_pos, int &_type_piece) {
		memset(_buf, 0, _size);

		int nums[5] = { _last_pos.x, _last_pos.y, _new_pos.x, _new_pos.y, _type_piece };
		int index = 0;
		for (int i = 0; i < 5; i++) {
			char num[2];
			itoa(nums[i], num, 10);
			_buf[index++] = num[0];
		}
		_buf[index] = 0;
	}

	void wait_enemy(sf::RenderWindow  &_window, SOCKET &acceptS, Player_action &_player_action) {
		const int size = 6;
		char buf[size];
		int bytesRecv = recv(acceptS, buf, size, 0);
		if (bytesRecv > 0) {
			read_buf(_player_action.last_pos, _player_action.new_pos, _player_action.new_piece, buf, size);
			_player_action.enemy_move(_player_action.last_pos, _player_action.new_pos, _player_action.new_piece, _window);
		}
		memset(buf, 0, size);
	}

	void window_opponent_wait(sf::RenderWindow  &_window) {
		_window.clear(sf::Color(200, 200, 200));

		sf::Font font;
		font.loadFromFile("Font//cour.ttf");
		sf::Text t;
		t.setString("Wating for the opponent...");
		t.setFont(font);
		t.setCharacterSize(28);
		t.setPosition(20, 236);
		t.setFillColor(sf::Color::Black);
		t.setStyle(sf::Text::Bold);

		_window.draw(t);
		_window.display();
	}

	void handle(sf::RenderWindow  &_window, Pieces_on_board &_pob, Player_action &_player_action) {
		SOCKET acceptS;
		SOCKADDR_IN addr_c;
		int addrlen = sizeof(addr_c);

		std::cout << "Client can connected..." << std::endl;
		window_opponent_wait(_window);
		if ((acceptS = accept(my_socket, (struct sockaddr*)&addr_c, &addrlen)) != 0) {
			std::cout << "Client is connected" << std::endl;
		}

		bool new_thread = false;
		while (_window.isOpen()) {
			sf::Event event;
			_window.pollEvent(event);

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				_window.close();

			_player_action.get_cursor().action();
			if (_player_action.get_whose_move() == false) {
				_player_action.selecting_piece(_pob);
				_player_action.make_move(_pob, _window);
				if (_player_action.get_whose_move() == true) {
					const int size = 6;
					char buf[size];
					serialize(buf, size, _player_action.last_pos, _player_action.new_pos, _player_action.new_piece);
					send(acceptS, buf, size, 0);
					memset(buf, 0, size);
					new_thread = true;
				}
			}
			else {
				if (new_thread == true) {
					new_thread = false;
					std::thread th(&Server::wait_enemy, this, std::ref(_window), std::ref(acceptS), std::ref(_player_action));
					th.detach();
				}
			}

			_window.clear(sf::Color(200, 200, 200));

			_pob.draw(_window);
			_player_action.get_cursor().draw(_window);
			_window.display();
			
			if (_player_action.get_end() == true) {
				if (_player_action.get_king_who_shah()) {
					if (_player_action.checkmate(_pob, _window, _player_action.get_king_who_shah()) == true) {
						if (_player_action.get_king_who_shah()->get_color() == true) {
							_player_action.notificaion(_window, "WHITE WIN", 29);
						}
						if (_player_action.get_king_who_shah()->get_color() == false) {
							_player_action.notificaion(_window, "BLACK WIN", 29);
						}
					}
				}
				_window.close();
				exit(0);
			}
		}
	}

private:
	unsigned short port;
	SOCKET my_socket;
	WSAData wData;
};