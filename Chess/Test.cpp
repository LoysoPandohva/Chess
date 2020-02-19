#include "Server.h"
#include "Client.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "Chess");

	Pieces_on_board pob;
	Player_action player_action(pob);

	Client client;
	Server server;
	if (client.start_client()) {
		client.handle(window, pob, player_action);
	}
	else {
		server.startServer();
		server.handle(window, pob, player_action);
	}
}

//#include <thread>
//#include <mutex>
//#include <iostream>
//using namespace std;
//
//class A {
//public:
//	int x = 0;
//	mutex mtx;
//
//	void a() {
//		for (size_t i = 1; i <= 10; i++) {
//			mtx.lock();
//			cout << "Thrad ID " << this_thread::get_id() << " a() --- " << i << endl;
//
//			std::this_thread::sleep_for(std::chrono::milliseconds(300));
//			mtx.unlock();
//		}
//	}
//
//	void t() {
//		thread th(&A::a, this);
//
//		for (size_t i = 1; i <= 10; i++) {
//			mtx.lock();
//			cout << "Thrad ID " << this_thread::get_id() << " t() --- " << i << endl;
//			std::this_thread::sleep_for(std::chrono::milliseconds(300));
//			mtx.unlock();
//		}
//
//		th.join();
//	}
//};
//
//int main() {
//	A a;
//
//	a.t();
//
//	for (size_t i = 1; i <= 10; i++) {
//		cout << "Thrad ID " << this_thread::get_id() << " --- " << i << endl;
//		std::this_thread::sleep_for(std::chrono::milliseconds(300));
//	}
//}