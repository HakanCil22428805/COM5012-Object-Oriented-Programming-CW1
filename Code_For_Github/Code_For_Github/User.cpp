#include "User.h"

User::User(std::string n) : name(n) {}
User::~User() {}

std::string User::getName() const {
	return name;
}

void User::setName(const std::string& newName) {
	name = newName;
}
