#include <catch2/catch.hpp>
#include "../include/CommandHandler.h"

TEST_CASE("parse simple command") {
    auto commandHandler = CommandHandler();
    const auto tokens = commandHandler.processCommand("*2\r\n$4\r\nPING\r\n$5\r\nHELLO\r\n");
    REQUIRE(tokens.size() == 2);
}
