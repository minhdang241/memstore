//
// Created by DANG BA MINH on 14/5/25.
//

#include "../include/CommandHandler.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * *2\r\n$4\r\nPING\r\n\$5\r\nHELLO\r\n
 */

CommandHandler::CommandHandler() = default;

auto CommandHandler::parseCommand(std::string const& command) -> std::vector<std::string> {
	std::cout << command << std::endl;
	auto tokens = std::vector<std::string>();
	if (command.empty())
		return tokens;
	if (command[0] == '*') {
		auto index = command.find("\r\n");
		if (index == std::string::npos)
			return tokens;
		auto const numElements = std::stoi(command.substr(1, index - 1));
		if (numElements == 0)
			return tokens;
		auto pos = index + 2;
		for (auto i = 0; i < numElements; i++) {
			if (pos >= command.size() or command[pos] != '$')
				break;
			index = command.find("\r\n", pos);
			if (index == std::string::npos)
				break;
			auto const length = std::stoi(command.substr(pos + 1, index - pos));
			pos = index + 2;
			if (pos + length > command.size())
				break;
			auto token = command.substr(pos, length);
			tokens.push_back(token);
			pos += length + 2;
		}
	}
	return tokens;
}

auto CommandHandler::processCommand(std::string const& command) -> std::string {
	std::cout << command << std::endl;
	auto tokens = parseCommand(command);
	if (tokens.empty()) {
		return "Error: empty commands\r\n";
	}
	for (auto const& token : tokens) {
		std::cout << token << std::endl;
	}
	auto cmd = tokens[0];
	std::ranges::transform(cmd, cmd.begin(), [](unsigned char c) { return std::toupper(c); });
	auto response = std::ostringstream();
	if (cmd == "COMMAND") {
		response << "*0\r\n";
	}
	else if (cmd == "PING") {
		response << "+PONG\r\n";
	}
	return response.str();
}
