#include "Harl.hpp"

Harl::Harl()
{
	levelFunctions[0] = &Harl::debug;
	levelFunctions[1] = &Harl::info;
	levelFunctions[2] = &Harl::warning;
	levelFunctions[3] = &Harl::error;
}

void Harl::debug()
{
	std::cout << "[DEBUG]"
						<< "\n"
						<< "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!"
						<< "\n"
						<< std::endl;
}

void Harl::info()
{
	std::cout << "[INFO]"
						<< "\n"
						<< "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!"
						<< "\n"
						<< std::endl;
}

void Harl::warning()
{
	std::cout << "[WARNING]"
						<< "\n"
						<< "I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month."
						<< "\n"
						<< std::endl;
}

void Harl::error()
{
	std::cout << "[ERROR]"
						<< "\n"
						<< "This is unacceptable! I want to speak to the manager now."
						<< "\n---------------------------------------------------------------------------------"
						<< std::endl;
}

void Harl::complain(std::string level)
{
	std::transform(level.begin(), level.end(), level.begin(), ToLower());
	int levelCode = ((level == "debug") * 1 + (level == "info") * 2 + (level == "warning") * 3 + (level == "error") * 4);

	switch (levelCode)
	{
	case 1:
		(this->*levelFunctions[0])();
	case 2:
		(this->*levelFunctions[1])();
	case 3:
		(this->*levelFunctions[2])();
	case 4:
		(this->*levelFunctions[3])();
		break;
	default:
		std::cout << "[" << level << "]"
							<< "\n"
							<< "Probably complaining about insignificant problems"
							<< "\n---------------------------------------------------------------------------------"
							<< std::endl;
		break;
	}
}