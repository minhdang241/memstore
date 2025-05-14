//
// Created by DANG BA MINH on 14/5/25.
//

#include "../include/Server.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <ostream>
#include <unistd.h>

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
		// Handle client connection
		char buffer[1024] = {0};
		read(client_socket_fd, buffer, sizeof(buffer));
		std::cout << buffer << std::endl;
		auto reply = std::string("Hello Client");
		send(client_socket_fd, reply.c_str(), reply.size(), 0);
	}
}

auto Server::stop() -> void {
	if (socket_fd > 0) {
		close(socket_fd);
	}
}
