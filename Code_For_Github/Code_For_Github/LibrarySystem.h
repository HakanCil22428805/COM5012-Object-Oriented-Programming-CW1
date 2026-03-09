#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <vector>
#include <string>
#include "Book.h"
#include "User.h"
#include "Member.h"

class LibrarySystem {
private:
	std::vector<Book*> books;
	std::vector<User*> users;

public:
	LibrarySystem();
	~LibrarySystem();

	void addBook(std::string title, std::string author);
	void removeBook(std::string title);

	Book* searchByTitle(std::string title);
	std::vector<Book*>searchByAuthor(std::string author);

	void viewBooksBasic() const;
	void viewBooksDetailed() const;

	void borrowBook(Member* member, std::string title);
	void reserveBook(Member* member, std::string title);
	void returnBook(Member* member, std::string title);

	bool addUser(User* user);
	User* findUser(const std::string name);
	void listUsers() const;

	void deleteUser(const std::string& name);
	void editUserName(const std::string& oldName, const std::string& newName);
};

#endif
