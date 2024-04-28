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
						<< "\n"
						<< std::endl;
}

void Harl::complain(std::string level)
{
	int levelCode = ((level == "DEBUG") * 1 + (level == "INFO") * 2 + (level == "WARNING") * 3 + (level == "ERROR") * 4);

	if (levelCode == 0)
		std::cout << "[" << level << "]"
							<< "\n"
							<< "Probably complaining about insignificant problems"
							<< "\n"
							<< std::endl;
	else
		(this->*levelFunctions[levelCode - 1])();
}
