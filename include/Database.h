//
// Created by DANG BA MINH on 15/5/25.
//

#ifndef DATABASE_H
#define DATABASE_H
#include <string>

// Database is a singleton class
class Database {
 public:
	static auto getInstance() -> Database&;

	auto dump(std::string const& filename) -> bool;
	auto load(std::string const& filename) -> bool;

	Database(Database const&) = delete;
	Database& operator=(Database const&) = delete;
	Database(Database&&) = delete;
	Database& operator=(Database&&) = delete;

 private:
	Database() = default;
	~Database() = default;
};

#endif // DATABASE_H
