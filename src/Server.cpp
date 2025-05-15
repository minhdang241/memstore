//
// Created by DANG BA MINH on 14/5/25.
//

#include "../include/Server.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <ostream>
#include <thread>
#include <unistd.h>
#include <vector>

#include "../include/CommandHandler.h"

Server::Server(int port)
: port(port)
, socket_fd(-1) {}

auto Server::start() -> void {
	// Create the welcome socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1) {
		std::cerr << "Failed to create socket" << std::endl;
		return;
	}

	// Config socket option
	int opt = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	// Config socket address
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(port);
	if (bind(socket_fd, reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address)) == -1) {
		std::cerr << "Failed to bind socket" << std::endl;
		close(socket_fd);
		return;
	}

	// Open welcome socket
	if (listen(socket_fd, SOMAXCONN) == -1) {
		std::cerr << "Failed to listen on socket" << std::endl;
		close(socket_fd);
		return;
	}

	std::cout << "Server listening on port " << port << std::endl;

	auto threads = std::vector<std::thread>();
	auto cmd_handler = CommandHandler();

	// Accept connections
	while (true) {
		sockaddr_in client_address;
		socklen_t client_address_length = sizeof(client_address);
		int client_socket_fd =
		    accept(socket_fd, reinterpret_cast<struct sockaddr*>(&client_address), &client_address_length);
		if (client_socket_fd == -1) {
			std::cerr << "Failed to accept connection" << std::endl;
			continue;
		}
		std::cout << "Client connected" << std::endl;
		threads.emplace_back([client_socket_fd, &cmd_handler]() {
			char buffer[1024];
			while (true) {
				memset(buffer, 0, sizeof(buffer));
				int bytes = recv(client_socket_fd, buffer, sizeof(buffer) - 1, 0);
				if (bytes == 0)
					break;
				auto request = std::string(buffer, bytes);
				auto response = cmd_handler.processCommand(request);
				send(client_socket_fd, response.c_str(), response.size(), 0);
			}
			close(client_socket_fd);
		});

		for (auto& t : threads) {
			if (t.joinable())
				t.join();
		}
	}
}

auto Server::stop() const -> void {
	if (socket_fd > 0) {
		close(socket_fd);
	}
}
