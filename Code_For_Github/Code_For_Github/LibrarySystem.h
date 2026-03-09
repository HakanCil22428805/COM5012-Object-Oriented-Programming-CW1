#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <vector>
#include <string>
#include "Book.h"
#include "User.h"
#include "Member.h"

//LibrarySystem class manages the entire library
//It stores books and users and controls system operations
class LibrarySystem {
private:

	//Vector storing pointers to all books and users in the library
	std::vector<Book*> books;
	std::vector<User*> users;

public:
	LibrarySystem();
	~LibrarySystem();

	//Book management functions
	void addBook(std::string title, std::string author);
	void removeBook(std::string title);

	//Search functions
	Book* searchByTitle(std::string title);
	std::vector<Book*>searchByAuthor(std::string author);

	//Book viewing functions
	//Used by members
	void viewBooksBasic() const;

	//Used by librarians
	void viewBooksDetailed() const;

	//Borrowing system
	void borrowBook(Member* member, std::string title);
	void reserveBook(Member* member, std::string title);
	void returnBook(Member* member, std::string title);

	//User management
	bool addUser(User* user);
	User* findUser(const std::string name);
	void listUsers() const;

	void deleteUser(const std::string& name);
	void editUserName(const std::string& oldName, const std::string& newName);
};

#endif
