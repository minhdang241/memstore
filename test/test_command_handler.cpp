#include "../include/CommandHandler.h"
#include <catch2/catch.hpp>

TEST_CASE("parse command") {
	const auto tokens = CommandHandler::parseCommand("*2\r\n$4\r\nPING\r\n$5\r\nHELLO\r\n");
	REQUIRE(tokens.size() == 2);
}
