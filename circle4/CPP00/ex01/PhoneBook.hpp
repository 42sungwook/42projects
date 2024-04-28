#pragma once
#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#define RED_TEXT "\033[1;31m"
#define BLUE_TEXT "\033[1;34m"
#define RESET_TEXT "\033[0m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"

class PhoneBook {
	public:
		PhoneBook();
		void addContact(const Contact& contact);
		void displayContacts() const;
		void searchContact(int index) const;

	private:
		static const int MAX_CONTACTS = 8;
		Contact contacts[MAX_CONTACTS];
		std::string truncateText(const std::string& text) const;
		int contactCount;
	};

#endif
