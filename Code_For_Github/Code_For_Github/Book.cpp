#include "Book.h"
#include "Member.h"
#include <iostream>

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
	if (reservedBy != nullptr) {
		borrowedBy = reservedBy;
		reservedBy = nullptr;
	}
	else {
		borrowedBy = nullptr;
	}
}
