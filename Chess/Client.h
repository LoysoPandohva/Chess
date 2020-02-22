#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include "Player_action.h"

#include <WinSock2.h>
#include <winsock.h>
#include <iostream>

class Client {
public:
	Client() : port(27015), lose_connection(false) {}

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
		c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		c_addr.sin_port = htons(port);

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
		close_client();
	}

	void close_client() {
		closesocket(c_sock);
		WSACleanup();
		std::cout << "Client was stoped. You can close app" << std::endl;
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

	void listen_opponent(sf::RenderWindow  &_window, SOCKET &acceptS, Player_action &_player_action) {
		const int size = 6;
		char buf[size];
		while (true) {
			int bytesRecv = recv(acceptS, buf, size, 0);
			if (bytesRecv > 0) {
				read_buf(_player_action.last_pos, _player_action.new_pos, _player_action.new_piece, buf, size);
				_player_action.opponent_move(_player_action.last_pos, _player_action.new_pos, _player_action.new_piece, _window);
			}
			if (bytesRecv <= 0) {
				std::cout << WSAGetLastError() << std::endl;
				lose_connection = true;
				return;
			}
			memset(buf, 0, size);
		}
	}

	void notification(sf::RenderWindow  &_window, const char _notification[]) {
		_window.clear(sf::Color(200, 200, 200));

		sf::Font font;
		font.loadFromFile("Font//cour.ttf");
		sf::Text t;
		t.setString(_notification);
		t.setFont(font);
		t.setCharacterSize(28);
		t.setPosition(20, 236);
		t.setFillColor(sf::Color::Black);
		t.setStyle(sf::Text::Bold);

		_window.draw(t);
		_window.display();
	}

	void show_time(sf::RenderWindow  &_window, const char _your_time[], const char _opponent_time[]) {
		static sf::Font font;
		static sf::Text t[2];
		static bool first_run = true;
		if (first_run == true) {
			font.loadFromFile("Font//cour.ttf");
			for (size_t i = 0; i < 2; i++) {
				t[i].setFont(font);
				t[i].setCharacterSize(30);
				t[i].setFillColor(sf::Color::Black);
				t[i].setStyle(sf::Text::Bold);
			}
			t[0].setPosition(510, 255);
			t[1].setPosition(510, 215);
			first_run = false;
		}
		t[0].setString(_your_time);
		t[1].setString(_opponent_time);

		for (size_t i = 0; i < 2; i++) {
			_window.draw(t[i]);
		}
	}
	void convert_time(int _time, char _res[]) {
		int min = _time / 60;
		int sec = _time % 60;

		char buf[3];
		itoa(min, buf, 10);
		if (min < 10) {
			_res[0] = '0';
			_res[1] = buf[0];
		}
		else {
			_res[0] = buf[0];
			_res[1] = buf[1];
		}
		_res[2] = ':';
		itoa(sec, buf, 10);
		if (sec < 10) {
			_res[3] = '0';
			_res[4] = buf[0];
		}
		else {
			_res[3] = buf[0];
			_res[4] = buf[1];
		}
	}
	char* your_time(bool _your_move, const int _game_time) {
		static sf::Clock clock;
		static int time = (int)clock.getElapsedTime().asSeconds();
		static int time_game = _game_time;
		static int time_left = _game_time;
		static int old_time = time;

		if (_your_move == false) {
			time = (int)clock.getElapsedTime().asSeconds();
			if (time != old_time) {
				old_time = time;
				time_left = time_game - time;
			}
		}
		else {
			time_game = time_left;
			clock.restart();
			old_time = time;
		}

		if (time_left <= 0) {
			static char end[4] = "end";
			return end;
		}

		static char res[6];
		convert_time(time_left, res);
		return res;
	}
	char* opponent_time(bool _whose_move, const int _game_time) {
		static sf::Clock clock;
		static int time = (int)clock.getElapsedTime().asSeconds();
		static int time_game = _game_time;
		static int time_left = _game_time;
		static int old_time = time;

		if (_whose_move == true) {
			time = (int)clock.getElapsedTime().asSeconds();
			if (time != old_time) {
				old_time = time;
				time_left = time_game - time;
			}
		}
		else {
			time_game = time_left;
			clock.restart();
			old_time = time;
		}

		if (time_left <= 0) {
			static char end[4] = "end";
			return end;
		}

		static char res[6];
		convert_time(time_left, res);
		return res;
	}

	void handle(sf::RenderWindow  &_window, Pieces_on_board &_pob, Player_action &_player_action) {
		std::thread th(&Client::listen_opponent, this, std::ref(_window), std::ref(c_sock), std::ref(_player_action));
		th.detach();

		while (_window.isOpen()) {
			char *ptr1 = your_time(_player_action.get_whose_move(), 300);
			char *ptr2 = opponent_time(_player_action.get_whose_move(), 300);

			sf::Event event;
			_window.pollEvent(event);

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				_window.close();

			_player_action.get_cursor().action();
			_player_action.selecting_piece(_window, _pob);
			if (_player_action.get_whose_move() == true) {
				_player_action.make_move(_pob, _window);
				if (_player_action.get_whose_move() == false) {
					const int size = 6;
					char buf[size];
					serialize(buf, size, _player_action.last_pos, _player_action.new_pos, _player_action.new_piece);
					send(c_sock, buf, size, 0);
					memset(buf, 0, size);
				}
			}

			_window.clear(sf::Color(200, 200, 200));

			_pob.draw(_window);
			_player_action.get_cursor().draw(_window);

			show_time(_window, ptr1, ptr2);

			_window.display();

			if (strcmp(ptr1, "end") == 0) {
				_player_action.notificaion(_window, "BLACK WIN", 29);
				close_app(_window);
			}
			if (strcmp(ptr2, "end") == 0) {
				_player_action.notificaion(_window, "WHITE WIN", 29);
				close_app(_window);
			}
			if (_player_action.get_end() == true) {
				if (_player_action.get_king_who_shah()->get_color() == true) {
					_player_action.notificaion(_window, "WHITE WIN", 29);
				}
				if (_player_action.get_king_who_shah()->get_color() == false) {
					_player_action.notificaion(_window, "BLACK WIN", 29);
				}
				_window.close();
				exit(0);
			}
			if (lose_connection == true) {
				while (true) {
					notification(_window, "     Lose connection");
					_window.pollEvent(event);
					if (event.type == sf::Event::Closed) break;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
						break;
					}
				}
				close_app(_window);
			}
		}
	}

	void close_app(sf::RenderWindow  &_window) {
		close_client();
		_window.close();
		exit(0);
	}
private:
	WSAData wData;
	SOCKET c_sock;
	SOCKADDR_IN c_addr;
	unsigned short port;
	bool lose_connection;
};