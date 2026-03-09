#ifndef MEMBER_H
#define MEMBER_H
#include "User.h"
#include <vector>

class Book;

class Member : public User {
private:
	std::vector<Book*> borrowedBooks;
	const int MAX_LIMIT = 5;

public:
	Member(std::string n);
	std::string getRole() const override;
	bool canBorrow() const;
	void addBorrowedBook(Book* book);
	void removeBorrowedBook(Book* book);
	int getBorrowCount() const;
	void viewBorrowedBooks() const;
	void setName(const std::string& newName);
};

#endif
