#pragma once

class User {
	int mode = 1;
	static User* user;
	User() = default;
	User(const User&) = delete;
	User& operator=(const User&) = delete;
public:
	static User* fetchUser() { return user; }
	int fetchMode() { return mode; }
	void changeUserMode() { mode = 0; }
	static void cleanUp() { delete user; user = nullptr; }
};
