#ifndef BOOK_H
#define BOOK_H
#include <string>

//Forward declaration of Member class
//This avoids circular dependency between Book and Member
class Member;

//Book class represents a single book in the library
class Book {
private:
	//Stores the title of the book
	std::string title;

	//Stores the author of the book
	std::string author;

	//Pointer to the member who borrowed the book
	Member* borrowedBy;

	//Pointer to the member who reserved the book
	Member* reservedBy;

public:
	//Constructor that initialises the book title and author
	Book(std::string t, std::string a);
	~Book();

	//Returns the title of the book
	std::string getTitle() const;

	//Returns the author of the book
	std::string getAuthor() const;

	//Returns the member currently borrowing the book
	Member* getBorrowedBy() const;

	//Returns the member who reserved the book
	Member* getReservedBy() const;

	//Checks if the book is currently available
	bool isAvailable() const;

	//Handles borrowing a book
	void borrow(Member* member);

	//Handles reserving a book
	void reserve(Member* member);

	//Handles returning a book
	void returnBook();
};

#endif
