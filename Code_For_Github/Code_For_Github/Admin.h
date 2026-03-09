//Header guard start. This prevents the file from being included multiple times
#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"

class Admin : public User {
public:

	//constructor that takes a name and passes it to the User constructor
	Admin(std::string n);

	//Overrides the pure virtual getRole() function from the User class
	//This allows polymorphism when checking user roles
	std::string getRole() const override;
};

#endif
// End of header guard
