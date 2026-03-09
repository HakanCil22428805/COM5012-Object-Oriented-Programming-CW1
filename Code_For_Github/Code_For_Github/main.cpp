#include <iostream>
#include "LibrarySystem.h"
#include "Admin.h"
#include "Member.h"
#include "Librarian.h"
using namespace std;

void clearInput() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void memberMenu(LibrarySystem& system, Member* member) {
	bool memberMenu = true;

	while (memberMenu) {
		cout << "\n--- MEMBER MENU ---\n";
		cout << "1. View Books\n";
		cout << "2. Search Book by Title\n";
		cout << "3. Search Book by Author\n";
		cout << "4. Borrow Book\n";
		cout << "5. Return Book\n";
		cout << "6. Reserve Book\n";
		cout << "7. View Borrowed Books.\n";
		cout << "0. Logout\n";
		cout << "Choice: ";

		int choice;

		if (!(cin >> choice)) {
			cout << "Invalid input.\n";
			clearInput();
			continue;
		}
		clearInput();

		string title, author;

		if (choice == 1) {
			system.viewBooksBasic();
		}
		else if (choice == 2) {
			cout << "Enter title: ";
			getline(cin, title);
			if (system.searchByTitle(title))
				cout << "Book found.\n";
			else
				cout << "Book not found.\n";
		}
		else if (choice == 3) {
			cout << "Enter author: ";
			getline(cin, author);
			{
				vector<Book*> results = system.searchByAuthor(author);
				if (results.empty()) {
					cout << "No books found.\n";
				}
				else {
					for (Book* b : results)
						cout << b->getTitle() << "\n";
				}
			}
		}
		else if (choice == 4) {
			cout << "Enter title: ";
			getline(cin, title);
			system.borrowBook(member, title);
		}
		else if (choice == 5) {
			cout << "Enter title: ";
			getline(cin, title);
			system.returnBook(member, title);
		}
		else if (choice == 6) {
			cout << "Enter title: ";
			getline(cin, title);
			system.reserveBook(member, title);
		}
		else if (choice == 7) {
			member->viewBorrowedBooks();
		}
		else if (choice == 0) {
			memberMenu = false;
		}
		else {
			cout << "Invalid option.\n";
		}
	}
}

void librarianMenu(LibrarySystem& system, Librarian* librarian) {
	bool librarianMenu = true;

	while (librarianMenu) {
		cout << "\n--- LIBRARIAN MENU ---\n";
		cout << "1. View Books\n";
		cout << "2. Add Book\n";
		cout << "3. Remove Book\n";
		cout << "0. Logout\n";
		cout << "Choice: ";

		int choice;

		if (!(cin >> choice)) {
			cout << "Invalid input.\n";
			clearInput();
			continue;
		}
		clearInput();

		string title, author;

		if (choice == 1) {
			system.viewBooksDetailed();
		}
		else if (choice == 2) {
			cout << "Enter title: ";
			getline(cin, title);
			cout << "Enter Author: ";
			getline(cin, author);
			system.addBook(title, author);
			cout << "Book added.\n";
		}
		else if (choice == 3) {
			cout << "Enter title: ";
			getline(cin, title);
			system.removeBook(title);
		}
		else if (choice == 0) {
			librarianMenu = false;
		}
		else {
			cout << "Invalid option.\n";
		}
	}
}

void adminMenu(LibrarySystem& system, Admin* admin) {
	bool adminMenu = true;

	while (adminMenu) {
		cout << "\n--- ADMIN MENU ---\n";
		cout << "1. Add Member\n";
		cout << "2. Add Librarian\n";
		cout << "3. View Users\n";
		cout << "4. Delete User\n";
		cout << "5. Edit User Name\n";
		cout << "0. Logout\n";
		cout << "Choice: ";

		int choice;

		if (!(cin >> choice)) {
			cout << "Invalid input.\n";
			clearInput();
			continue;
		}
		clearInput();

		if (choice == 1) {
			string newName;
			cout << "Enter member name: ";
			getline(cin, newName);
			if (system.addUser(new Member(newName))) {
				cout << "Member added.\n";
			}
		}
		else if (choice == 2) {
			string newName;
			cout << "Enter librarian name: ";
			getline(cin, newName);
			if (system.addUser(new Librarian(newName))) {
				cout << "Librarian added.\n";
			}
		}
		else if (choice == 3) {
			system.listUsers();
		}
		else if (choice == 4) {
			string name;
			cout << "Enter user to delete: ";
			getline(cin, name);
			system.deleteUser(name);
		}
		else if (choice == 5) {
			string oldName, newName;
			cout << "Enter user's name: ";
			getline(cin, oldName);
			cout << "Enter new name: ";
			getline(cin, newName);
			system.editUserName(oldName, newName);
		}
		else if (choice == 0) {
			adminMenu = false;
		}
		else {
			cout << "Invalid option.\n";
		}
	}
}

int main() {
	LibrarySystem system;

	Admin* admin = new Admin("SuperAdmin");
	system.addUser(admin);

	bool running = true;

	while (running) {
		cout << "\n===== SMART LIBRARY SYSTEM =====\n";
		cout << "1. Login\n";
		cout << "0. Exit\n";
		cout << "Choice: ";

		int mainChoice;

		if (!(cin >> mainChoice)) {
			cout << "Invalid input. Please enter a number.\n";
			clearInput();
			continue;
		}
		clearInput();

		if (mainChoice == 1) {
			string name;
			cout << "Enter your name: ";
			getline(cin, name);

			User* currentUser = system.findUser(name);
			if (!currentUser) {
				cout << "User not found.\n";
				continue;
			}

			if (currentUser->getRole() == "Admin")
				adminMenu(system, dynamic_cast<Admin*>(currentUser));

			else if (currentUser-> getRole() == "Member")
				memberMenu(system, dynamic_cast<Member*>(currentUser));

			else if (currentUser-> getRole() == "Librarian")
				librarianMenu(system, dynamic_cast<Librarian*>(currentUser));
		}
		else if (mainChoice == 0) {
			running = false;
		}
		else {
			cout << "Invalid option.\n";
		}
	}

	cout << "System shutting down...\n";
	return 0;
}
