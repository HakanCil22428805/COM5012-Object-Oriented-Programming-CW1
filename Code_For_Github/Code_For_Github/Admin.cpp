#include "Admin.h"

Admin::Admin(std::string n) : User(n) {}

std::string Admin::getRole() const {
	return "Admin";
}
