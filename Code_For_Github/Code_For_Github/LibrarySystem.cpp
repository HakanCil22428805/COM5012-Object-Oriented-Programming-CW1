#include "LibrarySystem.h"
#include "Librarian.h"
#include <iostream>

LibrarySystem::LibrarySystem() {}
LibrarySystem::~LibrarySystem() {

	//Delete every book object
	for (Book* b : books)
		delete b;

	for (User* u : users)
		delete u;
}

void LibrarySystem::addBook(std::string title, std::string author) {
	
	//Creates a new book object and stores its pointer
	books.push_back(new Book(title, author));
}

void LibrarySystem::removeBook(std::string title) {
	for (int i = 0; i < books.size(); i++) {

		//Check if the title matches
		if (books[i]->getTitle() == title) {

			//Prevents removal if the book is currently borrowed
			if (!books[i]->isAvailable()) {
				std::cout << "Cannot remove a borrowed book.\n";
				return;
			}

			delete books[i];

			//Remove pointer from vector
			books.erase(books.begin() + i);
			std::cout << "Book removed successfully.\n";
			return;
		}
	}
	std::cout << "Book not found.\n";
}

//Searches the library for a book with a specific title
Book* LibrarySystem::searchByTitle(std::string title) {

	//Loop through every book stored in the books vector
	for (Book* b : books) {

		//Compares the current book's title with the search title
		if (b->getTitle() == title)

			//If a match is found, return the pointer to that book
			return b;
	}

	//If no matching book is found, return nullptr
	return nullptr;
}

std::vector<Book*> LibrarySystem::searchByAuthor(std::string author) {

	//Creates a vector to store matching books
	std::vector<Book*> results;
	for (Book* b : books) {
		if (b->getAuthor() == author)

			//If it matches, add the book pointer to the results vector
			results.push_back(b);
	}
	return results;
}

//Displays a basic list of books (used by Members)
void LibrarySystem::viewBooksBasic() const {

	//Checks if the library currently has no books
	if (books.empty()) {
		std::cout << "No books available in the library.\n";
		return;
	}
	for (Book* b : books) {
		std::string borrowStatus;
		std::string reserveStatus;

		//Check if the book is currently borrowed
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

			//If someone borrowed the book, show their name
			<< " | Borrowed by: "
			<< (b->getBorrowedBy() ? b->getBorrowedBy()->getName() : "None")
			
			//If someone reserved the book, show their name
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

	//Checks if the book is already borrowed
	if (!book->isAvailable()) {
		std::cout << "Book not available.\n";
		return;
	}

	if (!member->canBorrow()) {
		std::cout << "Borrow limit reached.\n";
		return;
	}

	//Prevents the member from borrowing the same book again
	if (book->getBorrowedBy() == member) {
		std::cout << "You cannot reserve a book you have already reserved.\n";
		return;
	}

	//Prevents member from borrowing if they have already reserved it
	if (book->getReservedBy() == member) {
		std::cout << "You cannot reserve a book you have already borrowed.\n";
		return;
	}

	//Assigns the book to the member
	book->borrow(member);

	//Adds the book to the member's borrowed list
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

	//If the book is currently available, reservation is unnecessary
	if (book->getBorrowedBy() == nullptr) {
		std::cout << "Book is available. Borrow instead.\n";
		return;
	}

	//Prevents reserving a book the member has already borrowed
	if (book->getBorrowedBy() == member) {
		std::cout << "You cannot reserve a book you have already borrowed.\n";
		return;
	}

	if (book->getReservedBy() == member) {
		std::cout << "You cannot reserve a book you have already reserved.\n";
		return;
	}

	//Sets the reservation
	book->reserve(member);
	std::cout << "Book reserved.\n";
}

void LibrarySystem::returnBook(Member* member, std::string title) {
	Book* book = searchByTitle(title);

	if (!book) {
		std::cout << "Book not found.\n";
		return;
	}

	//If the book is not currently borrowed
	if (book->getBorrowedBy() == nullptr) {
		std::cout << "This book is not currently borrowed.\n";
		return;
	}

	//Prevents returning a book borrowed by someone else
	if (book->getBorrowedBy() != member) {
		std::cout << "You cannot return a book you did not borrow.\n";
		return;
	}

	book->returnBook();
	member->removeBorrowedBook(book);

	std::cout << "Book returned.\n";
}

//Adds a new user to the system
bool LibrarySystem::addUser(User* user) {

	//Checks if a user with the same name already exists
	if (findUser(user->getName()) != nullptr) {
		std::cout << "User with this name already exists.\n";

		//Delete the newly created user to prevent memory leaks
		delete user;
		return false;
	}
	//Adds the user pointer to the users vector
	users.push_back(user);
	return true;
}

//Searches for a user by name
User* LibrarySystem::findUser(const std::string name) {

	//Loops through all users
	for (User* u : users) {

		//Checks if the names match
		if (u->getName() == name)

			//Return pointer to that user
			return u;
	}

	//Return nullptr if user is not found
	return nullptr;
}

//Displays all registered users
void LibrarySystem::listUsers() const {
	std::cout << "\nAvailable Users:\n";

	//Loop through every user
	for (User* u : users) {

		//Display the user's name and role
		std::cout << "- " << u->getName()
			<< " (" << u->getRole() << ") \n";
	}
}

void LibrarySystem::deleteUser(const std::string& name) {

	//Loop through the user list
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->getName() == name) {

			//Prevent deleting the admin account
			if (users[i]->getRole() == "Admin") {
				std::cout << "Cannot delete admin account.\n";
				return;
			}

			//Free the memory of the user object
			delete users[i];

			//Remove the pointer from the vector
			users.erase(users.begin() + i);

			std::cout << "User deleted successfully.\n";
			return;
		}
	}
	std::cout << "User not found.\n";
}

void LibrarySystem::editUserName(const std::string& oldName, const std::string& newName) {
	
	//Prevent duplicate user names
	if (findUser(newName) != nullptr) {
		std::cout << "A user with this name already exists.\n";
		return;
	}

	//Find the existing user
	User* user = findUser(oldName);

	if (!user) {
		std::cout << "User not found.\n";
		return;
	}

	//If the user is a Member
	if (Member* m = dynamic_cast<Member*>(user)) {
		m->setName(newName);
	}

	//If the user is a Librarian
	else if (Librarian* l = dynamic_cast<Librarian*>(user)) {
		l->setName(newName);
	}

	//If the user is an Admin (not allowed)
	else {
		std::cout << "Admin name cannot be edited.\n";
		return;
	}
	std::cout << "User name updated successfully.\n";
}
