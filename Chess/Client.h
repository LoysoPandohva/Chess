#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include "Player_action.h"

#include <WinSock2.h>
#include <winsock.h>
#include <iostream>

class Client {
public:
	Client() {}

	bool start_client() {
		int iResult = WSAStartup(MAKEWORD(2, 2), &wData);
		if (iResult != NO_ERROR)
			printf("Error at WSAStartup()\n");

		c_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (c_sock == INVALID_SOCKET) {
			printf("Error at socket(): %ld\n", WSAGetLastError());
			WSACleanup();
		}

		c_addr.sin_family = AF_INET;
		// 192.168.0.104 - IP папиного ноутбука по домашней сети
		// 192.168.43.244 - IP папиного ноутбука от моего телефона
		// 192.168.0.103 - мой IP по домашней сети
		// 192.168.43.131 - мой IP от моего телефона
		c_addr.sin_addr.s_addr = inet_addr("192.168.0.104");
		c_addr.sin_port = htons(27015);

		if (connect(c_sock, (SOCKADDR*)&c_addr, sizeof(c_addr)) == SOCKET_ERROR) {
			std::cout << WSAGetLastError() << std::endl;
			printf("Failed to connect.\n");
			WSACleanup();
			return false;
		}

		printf("Client created\n");
		return true;
	}

	~Client() {
		WSACleanup();
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

	void handle(sf::RenderWindow  &_window, Pieces_on_board &_pob, Player_action &_player_action) {
		bool new_thread = true;
		while (_window.isOpen()) {
			sf::Event event;
			_window.pollEvent(event);

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				_window.close();

			_player_action.get_cursor().action();

			if (_player_action.get_whose_move() == true) {
				_player_action.selecting_piece(_pob);
				_player_action.make_move(_pob, _window);
				if (_player_action.get_whose_move() == false) {
					const int size = 6;
					char buf[size];
					serialize(buf, size, _player_action.last_pos, _player_action.new_pos, _player_action.new_piece);
					send(c_sock, buf, size, 0);
					memset(buf, 0, size);
					new_thread = true;
				}
			}
			else {
				if (new_thread == true) {
					new_thread = false;
					_window.setActive(false);
					std::thread th(&Client::wait_enemy, this, std::ref(_window), std::ref(c_sock), std::ref(_player_action));
					th.detach();
				}
			}
			_window.setActive(true);

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
	WSAData wData;
	SOCKET c_sock;
	SOCKADDR_IN c_addr;
};