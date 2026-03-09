#include "Member.h"
#include "Book.h"
#include <iostream>

Member::Member(std::string n) : User(n) {}

std::string Member::getRole() const {
	return "Member";
}

//Returns true if the member has borrowed fewer than the maximum allowed
bool Member::canBorrow() const {
	return borrowedBooks.size() < MAX_LIMIT;
}

//Adds a book pointer to the borrowedBooks vector
void Member::addBorrowedBook(Book* book) {
	borrowedBooks.push_back(book);
}

void Member::removeBorrowedBook(Book* book) {
	//Loop through the borrowed books
	for (int i = 0; i < borrowedBooks.size(); i++) {

		//Check if the current book matches the one being returned
		if (borrowedBooks[i] == book) {

			//Removes the book
			borrowedBooks.erase(borrowedBooks.begin() + i);
			return;
		}
	}
}

int Member::getBorrowCount() const {
	return borrowedBooks.size();
}

void Member::viewBorrowedBooks() const {

	//If the member has no books borrowed
	if (borrowedBooks.empty()) {
		std::cout << "You have not borrowed any books.\n";
		return;
	}

	std::cout << "\nYour Borrowed Books.\n";

	//Loop through each borrowed book
	for (Book* b : borrowedBooks) {

		//Displays title and author
		std::cout << "Title: " << b->getTitle()
			<< " | Author: " << b->getAuthor()
			<< "\n";
	}
}

void Member::setName(const std::string& newName) {
	name = newName;
}
