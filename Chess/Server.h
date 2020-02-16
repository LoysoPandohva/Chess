#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include "Player_action.h"

#include <WinSock2.h>
#include <winsock.h>
#include <iostream>

class Server {
public:
	Server() : port(27015) {	
		startServer();
	}

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

	void read_buf(sf::Vector2i &_from, sf::Vector2i &_to, char _buf[], int _size) {
		char num[2];
		int index_sym = 0;
		int nums[4];
		int indesx_num = 0;
		for (int i = 0; i < _size; i++) {
			if (_buf[i] != ',') {
				num[index_sym++] = _buf[i];
			}
			else {
				index_sym = 0;
				nums[indesx_num++] = atoi(num);
			}
		}
		_from = sf::Vector2i(nums[0], nums[1]);
		_to = sf::Vector2i(nums[2], nums[3]);
	}

	void serialize(char _buf[], int _size, sf::Vector2i &_last_pos, sf::Vector2i &_new_pos) {
		memset(_buf, 0, _size);

		int nums[4] = {_last_pos.x, _last_pos.y, _new_pos.x, _new_pos.y};
		int index = 0;
		for (int i = 0; i < 4; i++) {
			char num[2];
			itoa(nums[i], num, 10);

			if (num[i] != 0) {
				_buf[index++] = _buf[i];
			}
			else {
				_buf[index++] = ',';
			}
		}
	}

	void handle(sf::RenderWindow  &_window, Pieces_on_board &_pob, Player_action &_player_action) {
		SOCKET acceptS;
		SOCKADDR_IN addr_c;
		int addrlen = sizeof(addr_c);

		std::cout << "Client can connected..." << std::endl;
		if ((acceptS = accept(my_socket, (struct sockaddr*)&addr_c, &addrlen)) != 0) {
			std::cout << "Client is connected" << std::endl;
		}

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

				/*const int size = 12;
				char buf[size];
				serialize(buf, size, _player_action.last_pos, _player_action.new_pos);
				send(acceptS, buf, size, 0);*/
			}
			else {
				sf::Vector2i from;
				sf::Vector2i to;

				const int size = 9;
				char buf[size];
				int bytesRecv = recv(acceptS, buf, size, 0);
				if (bytesRecv > 0) {
					read_buf(from, to, buf, size);
					_player_action.anamy_move(_pob, from, to);
				}
				memset(buf, 0, size);
				_player_action.change_move();
				Sleep(50);
			}

			_window.clear(sf::Color(200, 200, 200));

			_pob.draw(_window);
			_player_action.get_cursor().draw(_window);
			_window.display();
		}
	}

private:
	unsigned short port;
	SOCKET my_socket;
	WSAData wData;
};