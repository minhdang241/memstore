#include "../include/Database.h"
#include "../include/Server.h"
#include <iostream>
#include <string>
#include <thread>

int main() {
	int port = 6379;
	auto server = Server(port);
	// Dump the database every 300 seconds
	auto const& filename = std::string("data.db");
	std::thread persistThread([filename]() {
		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(300));
			if (Database::getInstance().dump(filename)) {
				std::cout << "Database dumped" << std::endl;
			}
			else {
				std::cerr << "Database dump failed" << std::endl;
			};
		}
	});
	persistThread.detach();
	server.start();
	return 0;
}