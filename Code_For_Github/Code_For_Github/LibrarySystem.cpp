#include "LibrarySystem.h"
#include "Librarian.h"
#include <iostream>

LibrarySystem::LibrarySystem() {}
LibrarySystem::~LibrarySystem() {
	for (Book* b : books)
		delete b;

	for (User* u : users)
		delete u;
}

void LibrarySystem::addBook(std::string title, std::string author) {
	books.push_back(new Book(title, author));
}

void LibrarySystem::removeBook(std::string title) {
	for (int i = 0; i < books.size(); i++) {
		if (books[i]->getTitle() == title) {
			if (!books[i]->isAvailable()) {
				std::cout << "Cannot remove a borrowed book.\n";
				return;
			}

			delete books[i];
			books.erase(books.begin() + i);
			std::cout << "Book removed successfully.\n";
			return;
		}
	}
	std::cout << "Book not found.\n";
}

Book* LibrarySystem::searchByTitle(std::string title) {
	for (Book* b : books) {
		if (b->getTitle() == title)
			return b;
	}
	return nullptr;
}

std::vector<Book*> LibrarySystem::searchByAuthor(std::string author) {
	std::vector<Book*> results;
	for (Book* b : books) {
		if (b->getAuthor() == author)
			results.push_back(b);
	}
	return results;
}

void LibrarySystem::viewBooksBasic() const {
	if (books.empty()) {
		std::cout << "No books available in the library.\n";
		return;
	}
	for (Book* b : books) {
		std::string borrowStatus;
		std::string reserveStatus;

		if (b->getBorrowedBy() == nullptr)
			borrowStatus = "Not Borrowed";
		else
			borrowStatus = "Borrowed";

		if (b->getReservedBy() == nullptr)
			reserveStatus = "Not Reserved";
		else
			reserveStatus = "Reserved";

		std::cout << "Title: " << b->getTitle()
			<< " | Author: " << b->getAuthor()
			<< " | Borrow Status: " << borrowStatus
			<< " | Reserve Status: " << reserveStatus
			<< "\n";
	}
}

void LibrarySystem::viewBooksDetailed() const {
	if (books.empty()) {
		std::cout << "No books available in the library.\n";
		return;
	}
	for (Book* b : books) {
		std::cout << "Title: " << b->getTitle()
			<< " | Author: " << b->getAuthor()
			<< " | Borrowed by: "
			<< (b->getBorrowedBy() ? b->getBorrowedBy()->getName() : "None")
			<< " | Reserved by: "
			<< (b->getReservedBy() ? b->getReservedBy()->getName() : "None")
			<< "\n";
	}
}

void LibrarySystem::borrowBook(Member* member, std::string title) {
	Book* book = searchByTitle(title);
	
	if (!book) {
		std::cout << "Book not found.\n";
		return;
	}

	if (!book->isAvailable()) {
		std::cout << "Book not available.\n";
		return;
	}

	if (!member->canBorrow()) {
		std::cout << "Borrow limit reached.\n";
		return;
	}

	if (book->getBorrowedBy() == member) {
		std::cout << "You cannot reserve a book you have already reserved.\n";
		return;
	}

	if (book->getReservedBy() == member) {
		std::cout << "You cannot reserve a book you have already borrowed.\n";
		return;
	}

	book->borrow(member);
	member->addBorrowedBook(book);

	std::cout << "Borrow successful.\n";
}

void LibrarySystem::reserveBook(Member* member, std::string title) {
	Book* book = searchByTitle(title);

	if (!book) {
		std::cout << "Book not found.\n";
		return;
	}

	if (book->getReservedBy() != nullptr) {
		std::cout << "Book already reserved.\n";
		return;
	}

	if (book->getBorrowedBy() == nullptr) {
		std::cout << "Book is available. Borrow instead.\n";
		return;
	}

	if (book->getBorrowedBy() == member) {
		std::cout << "You cannot reserve a book you have already borrowed.\n";
		return;
	}

	if (book->getReservedBy() == member) {
		std::cout << "You cannot reserve a book you have already reserved.\n";
		return;
	}

	book->reserve(member);
	std::cout << "Book reserved.\n";
}

void LibrarySystem::returnBook(Member* member, std::string title) {
	Book* book = searchByTitle(title);

	if (!book) {
		std::cout << "Book not found.\n";
		return;
	}

	if (book->getBorrowedBy() == nullptr) {
		std::cout << "This book is not currently borrowed.\n";
		return;
	}

	if (book->getBorrowedBy() != member) {
		std::cout << "You cannot return a book you did not borrow.\n";
		return;
	}

	book->returnBook();
	member->removeBorrowedBook(book);

	std::cout << "Book returned.\n";
}

bool LibrarySystem::addUser(User* user) {
	if (findUser(user->getName()) != nullptr) {
		std::cout << "User with this name already exists.\n";
		delete user;
		return false;
	}
	users.push_back(user);
	return true;
}

User* LibrarySystem::findUser(const std::string name) {
	for (User* u : users) {
		if (u->getName() == name)
			return u;
	}
	return nullptr;
}

void LibrarySystem::listUsers() const {
	std::cout << "\nAvailable Users:\n";

	for (User* u : users) {
		std::cout << "- " << u->getName()
			<< " (" << u->getRole() << ") \n";
	}
}

void LibrarySystem::deleteUser(const std::string& name) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->getName() == name) {
			if (users[i]->getRole() == "Admin") {
				std::cout << "Cannot delete admin account.\n";
				return;
			}

			delete users[i];
			users.erase(users.begin() + i);

			std::cout << "User deleted successfully.\n";
			return;
		}
	}
	std::cout << "User not found.\n";
}

void LibrarySystem::editUserName(const std::string& oldName, const std::string& newName) {
	if (findUser(newName) != nullptr) {
		std::cout << "A user with this name already exists.\n";
		return;
	}

	User* user = findUser(oldName);

	if (!user) {
		std::cout << "User not found.\n";
		return;
	}

	if (Member* m = dynamic_cast<Member*>(user)) {
		m->setName(newName);
	}
	else if (Librarian* l = dynamic_cast<Librarian*>(user)) {
		l->setName(newName);
	}
	else {
		std::cout << "Admin name cannot be edited.\n";
		return;
	}
	std::cout << "User name updated successfully.\n";
}
