#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : contactCount(0) {}

std::string PhoneBook::truncateText(const std::string& text) const {
    std::string truncatedText = text;
    if (truncatedText.length() > 10) {
        truncatedText.resize(9);
        truncatedText += ".";
    }
    return truncatedText;
}

void PhoneBook::addContact(const Contact& contact) {
    if (contactCount >= MAX_CONTACTS) {
        for (int i = 0; i < MAX_CONTACTS - 1; ++i) {
            contacts[i] = contacts[i + 1];
        }
        contactCount = MAX_CONTACTS - 1;
    }
    contacts[contactCount] = contact;
    ++contactCount;
}

void PhoneBook::displayContacts() const {
    std::cout << YELLOW_TEXT << std::setw(10) << "Index" << "|"
    << std::setw(10) << "First Name" << "|"
    << std::setw(10) << "Last Name" << "|"
    << std::setw(10) << "Nickname" << RESET_TEXT << std::endl;

    for (int i = 0; i < contactCount; ++i) {
        std::cout << YELLOW_TEXT << std::setw(10) << (i + 1) << "|"
        << std::setw(10) << truncateText(contacts[i].getFirstName()) << "|"
        << std::setw(10) << truncateText(contacts[i].getLastName()) << "|"
        << std::setw(10) << truncateText(contacts[i].getNickname()) << RESET_TEXT << std::endl;
    }
}

void PhoneBook::searchContact(int index) const {
    if (index >= 0 && index < contactCount) {
        std::cout << GREEN_TEXT << "First Name: " << contacts[index].getFirstName() << "\n"
        << "Last Name: " << contacts[index].getLastName() << "\n"
        << "Nickname: " << contacts[index].getNickname() << "\n"
        << "Phone Number: " << contacts[index].getPhoneNumber() << "\n"
        << "Darkest Secret: " << contacts[index].getDarkestSecret() << RESET_TEXT << std::endl;
    } else {
        std::cout << RED_TEXT << "Invalid contact index." << RESET_TEXT << std::endl;
    }
}
