#ifndef BOOK_H
#define BOOK_H
#include <string>

class Member;

class Book {
private:
	std::string title;
	std::string author;
	Member* borrowedBy;
	Member* reservedBy;

public:
	Book(std::string t, std::string a);
	~Book();

	std::string getTitle() const;
	std::string getAuthor() const;

	Member* getBorrowedBy() const;
	Member* getReservedBy() const;

	bool isAvailable() const;

	void borrow(Member* member);
	void reserve(Member* member);
	void returnBook();
};

#endif
