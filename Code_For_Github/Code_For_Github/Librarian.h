#ifndef LIBRARIAN_H
#define LIBRARIAN_H
#include "User.h"

class Librarian : public User {
public:
	Librarian(std::string n);
	std::string getRole() const override;
};

#endif
