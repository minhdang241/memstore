//
// Created by DANG BA MINH on 14/5/25.
//

#include "../include/Database.h"

auto Database::getInstance() -> Database& {
	static auto instance = Database();
	return instance;
}

auto Database::dump(std::string const& filename) -> bool {
	return true;
}

auto Database::load(std::string const& filename) -> bool {
	return true;
}
