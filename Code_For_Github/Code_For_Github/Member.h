#ifndef MEMBER_H
#define MEMBER_H
#include "User.h"
#include <vector>

//Forward declaration to avoid circular dependency
class Book;

class Member : public User {
private:

	//Stores pointers to books currently borrowed by this member
	std::vector<Book*> borrowedBooks;

	//Maximum number of books a member can borrow
	const int MAX_LIMIT = 5;

public:
	Member(std::string n);

	//Overrides the pure virtual getRole() function from User
	std::string getRole() const override;

	//Checks if the member is allowed to borrow another book
	bool canBorrow() const;

	//Adds a book to the member's borrowed list
	void addBorrowedBook(Book* book);

	//Removes a returned book from the member's borrowed list
	void removeBorrowedBook(Book* book);

	//Returns how many books the member has currently borrowed
	int getBorrowCount() const;
	void viewBorrowedBooks() const;

	//Allows admin to update the member's name
	void setName(const std::string& newName);
};

#endif
