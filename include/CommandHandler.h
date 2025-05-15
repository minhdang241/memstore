//
// Created by DANG BA MINH on 14/5/25.
//

#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include <string>

class CommandHandler {
 public:
	CommandHandler();
	// Process a command from a client and return RESP-formatted response
	static auto parseCommand(std::string const& command) -> std::vector<std::string>;
	auto processCommand(std::string const& command) -> std::string;
};

#endif // COMMANDHANDLER_H
