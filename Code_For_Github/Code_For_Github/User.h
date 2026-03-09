#ifndef USER_H
#define USER_H
#include <string>

//Base class representing any user in the system
//This class will be inherited by Member, Librarian, and Admin
class User {
protected:

	//Stores the name of the user
	std::string name;

public:

	//Constructor that initialises the user's name
	User(std::string n);

	//Virtual destructor ensures correct cleanup when deleting derived objects through a base pointer
	virtual ~User();

	//Returns the user's name
	std::string getName() const;

	//Pure virtual function. This makes this an abstract class
	//All subclasses implement this function
	virtual std::string getRole() const = 0;

	//Allows the admin to change the user's name
	void setName(const std::string& newName);
};

#endif
