#include "Member.h"
#include "Book.h"
#include <iostream>

Member::Member(std::string n) : User(n) {}

std::string Member::getRole() const {
	return "Member";
}

bool Member::canBorrow() const {
	return borrowedBooks.size() < MAX_LIMIT;
}

void Member::addBorrowedBook(Book* book) {
	borrowedBooks.push_back(book);
}

void Member::removeBorrowedBook(Book* book) {
	for (int i = 0; i < borrowedBooks.size(); i++) {
		if (borrowedBooks[i] == book) {
			borrowedBooks.erase(borrowedBooks.begin() + i);
			return;
		}
	}
}

int Member::getBorrowCount() const {
	return borrowedBooks.size();
}

void Member::viewBorrowedBooks() const {
	if (borrowedBooks.empty()) {
		std::cout << "You have not borrowed any books.\n";
		return;
	}

	std::cout << "\nYour Borrowed Books.\n";

	for (Book* b : borrowedBooks) {
		std::cout << "Title: " << b->getTitle()
			<< " | Author: " << b->getAuthor()
			<< "\n";
	}
}

void Member::setName(const std::string& newName) {
	name = newName;
}
