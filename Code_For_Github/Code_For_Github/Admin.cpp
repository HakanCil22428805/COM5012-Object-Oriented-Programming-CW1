#include "Admin.h"

//Admin constructor
//The colon syntax callsthe base class constructor (User) and passes the name
Admin::Admin(std::string n) : User(n) {}

//Returns the role of this user
//Used in the system to determine permissions and menu access
std::string Admin::getRole() const {
	return "Admin";
}
