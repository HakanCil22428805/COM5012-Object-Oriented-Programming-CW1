#include "Book.h"
#include "Member.h"
#include <iostream>

//Constructor for book
//Initialises title, author, and sets borrowedBy and reservedBy to nullptr
Book::Book(std::string t, std::string a) : title(t), author(a), borrowedBy(nullptr), reservedBy(nullptr) {}

Book::~Book() {}

std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }

Member* Book::getBorrowedBy() const { return borrowedBy; }
Member* Book::getReservedBy() const { return reservedBy; }

bool Book::isAvailable() const {
	return borrowedBy == nullptr;
}

void Book::borrow(Member* member) {
	borrowedBy = member;
}

void Book::reserve(Member* member) {
	reservedBy = member;
}

void Book::returnBook() {
	//If someone reserved the book
	if (reservedBy != nullptr) {

		//Transfers the book to the reserver
		borrowedBy = reservedBy;

		//Clears the reservation
		reservedBy = nullptr;
	}

	//If no reservation exists
	else {

		//Marks the book as available
		borrowedBy = nullptr;
	}
}
