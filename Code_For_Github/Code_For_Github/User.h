#ifndef USER_H
#define USER_H
#include <string>

class User {
protected:
	std::string name;

public:
	User(std::string n);
	virtual ~User();
	std::string getName() const;
	virtual std::string getRole() const = 0;
	void setName(const std::string& newName);
};

#endif
