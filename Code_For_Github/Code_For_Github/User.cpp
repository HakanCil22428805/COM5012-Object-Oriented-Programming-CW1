#include "User.h"

//Constructor for User
//Initialises the name variable using an initialiser list
User::User(std::string n) : name(n) {}

//Virtual destructor
//It ensures derived classes are destroyed correctly
User::~User() {}

//Returns the name of the user
std::string User::getName() const {
	return name;
}

//Allows the name of the user to be updated
//Used when the admin edits user details
void User::setName(const std::string& newName) {
	//Assigns the new name to the name variable
	name = newName;
}
