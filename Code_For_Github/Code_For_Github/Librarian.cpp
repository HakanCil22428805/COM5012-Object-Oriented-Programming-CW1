#include "Librarian.h"

Librarian::Librarian(std::string n) : User(n) {}

std::string Librarian::getRole() const {
	return "Librarian";
}
