#include "PhoneBook.hpp"
#include <sstream>

std::string getInput(const std::string& message, const std::string& errorMessage) {
	std::string input;
	
	std::cout << BLUE_TEXT << message << RESET_TEXT;
	if (!std::getline(std::cin, input) || input.empty()) {
		std::cout << RED_TEXT << errorMessage << RESET_TEXT << std::endl;
		return "";
	}
	return input;
}

bool	commandAdd(PhoneBook& phoneBook) {
		std::string firstName, lastName, nickname, phoneNumber, darkestSecret;

		firstName = getInput("Enter First Name: ", "First Name cannot be empty.");
		if (firstName.empty()) return false;

		lastName = getInput("Enter Last Name: ", "Last Name cannot be empty.");
		if (lastName.empty()) return false;

		nickname = getInput("Enter Nickname: ", "Nickname cannot be empty.");
		if (nickname.empty()) return false;

		phoneNumber = getInput("Enter Phone Number: ", "Phone Number cannot be empty.");
		if (phoneNumber.empty()) return false;

		darkestSecret = getInput("Enter Darkest Secret: ", "Darkest Secret cannot be empty.");
		if (darkestSecret.empty()) return false;

		Contact newContact(firstName, lastName, nickname, phoneNumber, darkestSecret);
		phoneBook.addContact(newContact);
		return true;
}

bool commandSearch(PhoneBook& phoneBook) {
    phoneBook.displayContacts();

    std::string indexStr;
    int index;

    std::cout << BLUE_TEXT << "Enter the index of the contact to display: " << RESET_TEXT;
    if (!std::getline(std::cin, indexStr)) {
        return false;
    }

    std::istringstream iss(indexStr);
    if (!(iss >> index)) {
        return false;
    }

    phoneBook.searchContact(index - 1);
    return true;
}

int main() {
	PhoneBook phoneBook;
	std::string command;

	while (true) {
		std::cout << "Enter a command (ADD, SEARCH, EXIT): ";

		if (!std::getline(std::cin, command)) {
			std::cout << "EXIT" << std::endl;
			break;
		}

		if (command == "ADD") {
			if (!commandAdd(phoneBook)) {
				std::cout << RED_TEXT << "Invalid input." << RESET_TEXT << std::endl;
				continue;
			}
		}
		else if (command == "SEARCH") {
			if (!commandSearch(phoneBook)) {
				std::cout << RED_TEXT << "Invalid index." << RESET_TEXT << std::endl;
				continue;
			}
		}
		else if (command == "EXIT") {
			break;
		}
		else {
			if (!command.empty())
					std::cout << RED_TEXT << "Invalid command." << RESET_TEXT << std::endl;
		}
	}
	return 0;
}
