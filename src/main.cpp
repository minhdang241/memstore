#include "../include/Server.h"
#include <iostream>
#include <thread>

int main() {
	int port = 6379;
	auto server = Server(port);
	// Dump the database every 300 seconds
	std::thread persistThread([]() {
		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(300));
			// dump the data
		}
	});
	persistThread.detach();
	server.start();
	return 0;
}